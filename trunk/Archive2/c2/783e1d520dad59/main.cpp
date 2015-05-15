#ifdef __THREADTRANSPORT_H__
#define __THREADTRANSPORT_H__

#ifndef OSIP_MT
#define OSIP_MT
#endif

#include <osip2/osip.h>
#include <osipparser2/osip_parser.h>
#include <osip2/osip_mt.h>

#include "baseuint.h"
#include "ThreadBase.h"
#include "Node.h"

class Node ;

class ThreadTransport : public ThreadBase
{
    /**
    这种写一个线程基类的方法貌似很有用，
    以前从来没有见过这种东西
    */
protected :
    // int sec_max ;
    // int usec_max ;
    int in_port ;
    int in_socket ;
    int out_port ;
    int out_socket ;
    
    int mcast_socket ;
    
    
    Node *admin_core ;
    
public :
    // 侦听并且接收消息
    int tran_rcv_message ( int max ) ;
    
    int tran_snd_message ( osip_transaction_t *transaction , // read only element 
        osip_message_t * message , // message to send 
        char *host ,  // proposed destination host ip
        int port ,    // proposed destination host port 
        int socket ) ; // proposed socket ( if any ) 

    // here is how to deal with the message
    int tran_process_message ( char *buf , char *ip_addr , int port , int length ) ;
    
private :
    int __osip_message_fix_last_via_header( osip_message_t *request ,
            char *ip_addr , int port ) ;

public :
    // constructor 
    ThreadTransport ( Node *node ) ;
    ~ThreadTransport () ;

    int Transport_execute( int sec_max , int usec_max , int max_analysed ) ;

} ;



#endif