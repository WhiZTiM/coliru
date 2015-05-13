#ifndef _THREADBASE_H__
#define _THREADBASE_H__

#include "pipe.h"
// 这里主要实现了线程之间的协调功能

class ThreadBase
{
public :
    void *thread ; // thread
    jpipe_t wakeup ;
    
public :
    ThreadBase () ; // constructor
    ~ThreadBase () ; // destructor 
    
    int ThreadRelease (0 ;
    int ThreadStart ( void *(*func_start) ( void *) , void *arg ) ;
    int ThreadWakeUp() ; // wake up the thread 
} ;

#endif