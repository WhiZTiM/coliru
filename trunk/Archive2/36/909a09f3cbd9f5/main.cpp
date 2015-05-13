#ifndef _PIPE_H_
#define _PIPE_H_

#ifndef WIN32
#ifndef HAVE_UNISTD_H
#include <unistd.h>
#endif 
#endif 

#ifdef WIN32

#include <winsocket.h>
#endif

// what 's this used for ?
class jpipe_t
{
private :
    int pipes[2] ;
public :
    // get new pipe pair . 
    jpipe_t (void ) ;
    
    // close pipe
    ~jpipe_t () ;
    
    // write in a pipe
    int jpipe_write ( const void *buf , int count ) ;
    
    // read in a pipe 
    int jpipe_read ( void *buf , int count ) ;
    
    // get descriptor or reading pipe
    int jpipe_get_read_descr () ;
    
} ;