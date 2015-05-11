#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <cstdio>
#include <cstdlib>
#include <iostream>

/**
this file is used to justify the difference between boost::scoped_ptr and boost::shared_ptr
results:
1. shared_ptr can hands in its possion on an object , however the scoped_ptr doesn't 
2. when you write something to let scoped_ptr hands in its possion on some object
    spaces allocated to that object will be released immediately
    but , unfortunately the output contents won't be shown on the screen cause the error message
    
    by Aimer
*/



template <typename T>
class sharedPtr
{
    public :
    typedef boost::shared_ptr<T> type ;
} ;

template <typename T>
class scopedPtr
{
    public :
    typedef boost::scoped_ptr<T> type ;
} ;

class obj 
{
    public :
      obj ( std::string& n )
     {
         name = n ;
         std::cout << "you get a obj " << name << std::endl ;
     }
     
     void print ()
     {
         std::cout << "the programmer loves " <<name << std::endl ;
     }
     
     ~obj ()
     {
        std::cout << "good bye " << name << std::endl;
     }
     
     private :
     std::string name ;
} ;


int main ( void )
{
    std::string name ("kylin_zhang") ;
    
    // first we test whether shared_ptr can transfer the possion of a obj instance
    sharedPtr<obj>::type p1 (new obj(name)) ;
    sharedPtr<obj>::type p2 = p1 ;
    
    p2->print () ;
    
    std::string name_ ("singer aimer") ;
    // then we test whether the scoped_ptr can hand in its possion of a obj
    scopedPtr<obj>::type q1 (new obj(name_)) ;
    
    
    std::cout << "here we will transfer the posssion from q1 to q2" <<std::endl;
    scopedPtr<obj>::type q2 = q1 ;
    q2->print () ;
    
    
    return 0 ;
}