#ifndef __CHORDID_H__
#define __CHORDID_H__

#include "baseuint.h"

class ChordId
{
private :
    BitInt id ;                 /// this is index
    char address[50] ;          /// this is ip address
    char port[10] ;             // this is port
    void *constants ;           /// this is constants
public :
    // ChordId   ;
    ChordId(BitInt i = -1 , void *cons = NULL , const char *a = NULL ,
            const char *p = NULL ) ;
            
    ChordId ( char *a , char *p , void *cons ) ;
    
    unsigned int shash( char *str ) ;
    BitInt GetId () ;
    char * GetId_str () ;
    void SetId( int i ) ;
    char * GetAddress () ;
    void SetAddress ( const char *addr ) ;
    char *GetPort () ;
    void SetPort ( const char * p ) ;
    
    // if id = 0 , return true 
    bool IsEmptyChordId () ;
    bool BelongsRightInclusive( ChordId first ,  ChordId second ) ;
    bool belongs ( ChordId first , ChordId second ) ;
    bool isLower ( ChordId anotherId ) ;
    
    bool isGreater( ChordId anotherId ) ;
    ChordId add ( ChordId bId ) ;
    ChordId substract ( ChordId bId ) ;
    int msb () ;
    int compareTo(ChordId obj ) ;
    bool equals (ChordId obj ) ;
    
    bool EqualsWithAddr ( ChordId obj ) ;
    char *toString () ;
    
     
} ;



#endif
