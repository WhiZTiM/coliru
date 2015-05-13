#ifndef OSIP_MT
#define OSIP_MT
#endif

#include <osip2/osip_mt.h>
#include <osip2/osip_condv.h>
#include <osip2/osip.h>

#include "baseuint.h"
#include "ThreadBase.h"

//-------------------------------------------
ThreadBase::ThreadBase():wakeup()
{
    thread = NULL ;
}

//-------------------------------------------
ThreadBase::~ThreadBase()
{
    if ( thread != NULL )
    {
        ThreadRelease() ;
        OSIP_TRACE ( osip_trace (__FILE__ , __LINE__ , OSIP_BUG, NULL ,
                "You must call module_release() before calling module_free() \n") ) ;
        return ;
    }
}

//----------------------------------------------
int ThreadBase::ThreadRelease ()
{
    char q[2] = "q" ;
    int i ;
    
    if (thread == NULL )
        return 0 ; 
        
    i = wakeup.jpipe_write ( &q , 1 ) ;
    // write "q" into the pipe 
    if ( i != 1 ) //means writer error 
    {
        OSIP_TRACE( osip_trace (__FILE__, __LINE__ , OSIP_ERROR , NULL ,
                "could not write in pipe\n")) ;
        return -1 ;
    }
    
    i = osip_thread_join((struct osip_thread*)thread) ;
    // if osip_thread_join executed success return 0     
    
    if ( i != 0 )
    {
        OSIP_TRACE(osip_trace (__FILE__, __LINE__ , OSIP_ERROR , NULL ,
            "could not shutdown thread! \n")) ;
            
        return -1 ;
    }
    
    osip_free ( thread ) ;
    thread = NULL ;
    return 0 ;
}

//-----------------------------------
int ThreadBase::ThreadStart ( void *(*func_start)(void*) , void *arg )
{
    if ( func_start == NULL )
        return -1 ;
    thread = (void *)osip_thread_create( 20000 , func_start , arg ) ;
    if ( thread = NULL )
        return -1 ;
        
    return 0 ;
    
    // got it , but how to call this method run
}

//-----------------------------
int ThreadBase::ThreadWakeUp()
{
    /**
     是什么方法让 thread sleep ？
     为何又要让他 wakeup
     i know  how , but i donot know why ?
    */
    
    int i ;
    char q[2] = "w" ;
    
    i = wakeup.jpipe_write ( &q , 1 ) ;
    if ( i != 1 )
    {
        OSIP_TRACE( osip_trace (__FILE__ , __LINE__ , 
                OSIP_ERROR , NULL , "could not write in pipe!\n")) ;
        perror ( "error while writing in pipe ") ;
        
        return  -1 ;
    }
    
    return 0 ;    
}





















