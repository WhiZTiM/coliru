#include <cstdio>
#include <iostream>
#include <cstdlib>

/**
 this test is used to testify how does explicit works on class ' s constructors 

 by Aimer 5/11/2015
**/




class obj1
{
public :
   explicit  obj1 ( const obj1 & o )
   {
       name = o.name+"  copyed " ;
   }
   
   explicit obj1 ( std::string& n )
    {
        name = n ; 
    }
    void print ()
    {
        std::cout << " my name is obj1's " << name << std::endl ;
    }
public :
    std::string name ;

} ;

class obj2
{
public :
    obj2( const obj2 &o)
    {
        name = o.name+" copyed " ;
    }
    
    obj2( std::string & n )
    {
        name = n;
    }
    
    void print ()
    {
        std::cout << "my name is obj2's " << name << std::endl ;
    }
    
    private :
    std::string name ;

} ;


int main ( )
{
    std::string name ("kylin") ;
    
std::cout << "ok here we test the explicit obj1's string and non-explicit obj2's string constructor " << std::endl ;
    
    
    /*
    this will arise error , cause the explicit of string parameter constructor  
    obj1 obj1_1 = name ;
    obj1_1.print() ;
    */
    
    // this will be ok 
    obj2 obj2_1 = name ; 
    obj2_1.print () ;
    
std::cout << "---------------------------------------------------------------------------------------------"<<std::endl ;
std::cout << "ok here we test the explicit obj1's string and non-explicit obj2's object & constructors " << std::endl ;
    
    /**
       right ! , following codes will arise error again , because of the explicit 
       
       obj1 obj1_2 = obj1_1 ;
       obj1_2.print () ;
    */
    obj1 obj(name) ; // here we creates an obj1 's instance in right rules
    obj.print () ;  // if this work , it means every goes well in obj 
    
    obj1 obj1_3 (obj) ; // this line goes all right , cause explicit could not detect this , you can use noncopyable from boost 
                        // to ban this , may be that's why we will use boost::noncopyable 
    obj1_3.print () ;
    
    obj2 obj2_2 = obj2_1 ;
    obj2_2.print () ;
    
    
    return 0 ;
    
}