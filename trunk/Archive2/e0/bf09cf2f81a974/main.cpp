#ifndef __FINGERTABLE_H__
#define __FINGERTABLE_H__


#include "baseuint.h"
#include "ChordId.h"
#include "Constants.h"

// the struct of FingerTable Entry
struct Finger
{
    ChordId node ;
    ChordId start ;
    ChordId interval[2] ;  // well what's this used for ?
} ;

class Node ;
class FingerTable 
{
private :
    Finter fingers [NBITS] ; // this means that bits of a node's id is equal to the 
                             // how many elements can a finger table contain 
    void *constants ; // what's this ? 
    
    ChordId         predecessor ; // this is the finger table's precessor's Chord Node Id 
    ChordId         successsor[NSUCCLIST] ;
    // what predecessor is only one and the successor are multi?
    
    Node *localnode ; // the local node 
    
    
public :
    
    FingerTable () {} ;
    FingerTable ( void *const , Node *node ) ;
    ~FingerTable () ;
    void initfigners () ;
    Finger *getFinger ( int position ) ;
    int getTableLength () ;
    void setFinger ( int position , Finger finger ) ;
    
    
public :
     ChordId getPredecessor () ;
     void setPredecessor(ChorId pred ) ;
     ChordId getSuccessor ( int pos ) ; // 0 ~NSUCCLIST
     void setSuccessor ( int pos , ChordId succ ) ;
     int getSuccNum () ;
     void clearSuccList () ;


public :
    int toString ( char **buf , unsigned int & length ) ;
    /***
    这个地方的代码是唯一能够读懂的，
    返回值对应的是参数，同时，
    length 对应的是返回值对应的长度
    
    */


} ;




#endif 