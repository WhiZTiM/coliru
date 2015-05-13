#include <osipparser2/osip_port.h>
#include "pipe.h"

#ifndef WIN32

jpipe_t::jpipe_t ()
{
    if ( 0 != pipe( pipes))
    {
        // this is something wrong when we call pipe method to create a pipe
        return ;
    }
}

jpipe::~jpipe_t ()
{
    close ( apipe->pipes[0]);
    close ( apipe->pipes[1])
}

// fd of write is 1

// write in a pipe
int jpipe_t::jpipe_write ( const void *buf , int count )
{
    return write ( pipes[1] , buf, count ) ;
}

// and here we known that fd of read is 0
// this is the standard input file descriptor 
// read in a pipe
int jpipe_t::jpipe_read ( void *buf , int count )
{
    return read ( pipes[0] , buf , count ) ;
}

// get a descriptor of reading pipe
int jpipe_t::jpipe_get_read_descr()
{
    return apipe->pipes[0] ;
}


#else

jpipe_t::jpipe_t ()
{
    int s = 0 ;
    int timeout = 0 ;
    static int aport = 10500 ;
    struct sockaddr_in raddr ;
    int j ;
    
    s = (int) socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP) ;
    if ( 0 > s )
    {
        // s < 0 means something wrong we we call socket method
        return ;
    }
    
    // and we also know that pipes[1] is used as the write in pipe descriptor 
    pipes[1] = (int) socket( PF_INET, SOCK_STREAM , IPPROTO_TCP) ;
    if (  0 > pipes[1] )
    {
        closesocket( s ) ;
        // error happend when we call socekt
        reutrn ;
    }
    
    radd.sin_add.s_addr = inet_addr ("127.0.0.1") ;
    raddr.sim_family = AF_INET ;
    
    j  = 50 ; // total try 50 times
    
    while ( aport++ && j--  > 0 ) // find a good port number
    {
        raddr.sin_port = htons((short) aport ) ;
            
        if ( bind(s, (struct sockaddr *)&raddr, sizeof(raddr)) < 0 )
        {
            OSIP_TRACE(osip_trace( __FILE__, __LINE__ , OSIP_WARNING, NULL ,
                "Failed to bind one local socket : %i !\n" , aport )) ;
        }
        
        else
            break ;
    }
    
    if ( j == 0 )
    {
        OSIP_TRACE (osip_trace(__FILE__ , __LINE__ , OSIP_ERROR, NULL ,
                "Failed to bind a local socket , aborting !\n")) ;
        closesocket (s) ; // windows close socket method 
    }
    
    j = listen ( s , 1 ) ;
    
    if ( j != 0 )
    {
        OSIP_TRACE(osip_trace(__FILE__, __LINE__, OSIP_ERROR , NULL ,
                "Failed to listen on a local socket , aborting! \n")) ;
                
        closesocket ( s ) ;
        closesocket ( pipes[1]) ;
        
        return ;
    }
    
    
    j = setsocketopt ( pipes[1] , SOL_SOCKT , SO_RCVTIMEO ,
            (const char *)&timeout , sizeof(timeout)) ;
            
    
    if ( j != NO_ERROR )
    {
        // failed for some reason
        OSIP_TRACE ( osip_trace (__FILE__ , __LINE__ , OSIP_ERROR , NULL ,
                "udp plugin can not set O_NONBLOCK to the file descritpor !\n ")
    
    
        closesocket ( s ) ;
        closesocket ( pipes[1]) ;
        
        return ;
    }
    
    
    connect ( pipes[1] , ( struct sockaddr *) &addr , sizeof(raddr)) ;
    
    pipes[0] = accept ( s , NULL , NULL ) ;
    
    // pipes[0] is used for reading 
    
    if ( pipes[0] <= 0 )
    {
        OSIP_TRACE( osip_trace ( __FILE__, __LINE__ , OSIP_ERROR , NULL ,
            "udp plugin ; Failed to call accept !\n")) ;
            
            closesocket ( s ) ;
            closesocket ( pipes[1] ) ;
            return ;
    }
    
    
}


jpipe:~jpipe()
{
    closesocket ( pipes[0] ) ;
    closesocket ( pipes[1] ) ;
}

// write in a pipe
int jpipe_t::jpipe_write( const void *buf , int count )
{
    return send ( pipes[1] , ( const char *)buf , count , 0 ) ;
}

// read in a pipe
int jpipe_t::jpipe_read( void *buf , int count )
{
    return recv( pipes[0] , (char *)buf , count , 0 /*MSG_DONTWAIT*/ ) ;
}

// get descriptor of reading pipe
int jpipe_t::jpipe_get_read_descr ()
{
    return pipes[0] ;
}

#endif 