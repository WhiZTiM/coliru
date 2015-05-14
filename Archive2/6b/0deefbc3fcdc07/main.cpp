// AdOsip.h

#ifndef __ADOSIP_H__
#define __ADOSIP_H__

#include <osip2/osip.h>
#include <osipparser2/osip_parser.h>
#include <osip2/osip_mt.h>
#include "ThreadBase.h"

class AdOsip : public ThreadBase
{
public :
    // osip main element 
    osip_t *j_osip ;
    
    // delay between update (should be 500ms)
    int delay ;
    
    // osip_transaction list
    osip_list_t         *j_transactions ;
    
    void                *j_cond ;
    
    // the lock of this osip library
    void                *j_mutexlock ;
    
    int                 exit_flag ;
        
            
            
    // basic statistics
    int total_ict ;
    int successfull_ict ;
    int total_nict ;
    int successfull_nict ;
    int total_ist ;
    int successfull_ist ;
    int total_nist ;
    int successfull_nist ;

private :
    // void _osip_kill_transaction( osip_list_t* transactions ) ;
    // callback_t j_call_callbacks[EXOSIP_CALLBACK_COUNT] ;
    
    // kill the transaction 
    void _osip_kill_transaction ( osip_list_t * transactions ) ;
    
    
public :
    // constructor 
    AdOsip () ;
    // destructor
    ~AdOsip () ;
    
    
    osip_t *GetOsip () ;
    
    // lock/unlock the osip library
    AdOsip_lock ();
    AdOsip_unlock () ;

    // set callbacks
    int AdOsip_Set_Callback () ;


    // set dealy 
    void AdOsip_set_dealy ( int dly ) ;
    
    
    // Exec osip stack 
    int AdOsip_execute () ;
    
private :
    // call callbacks 
    // void report_event_with_status( event_t * je , osip_message_t *sip ) 

} ;




#endif