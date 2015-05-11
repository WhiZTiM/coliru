#include <cstdio>
#include <iostream>
#include <cstdlib>

class obj
{
public :
    obj ( std::string n )
    {
        name = n ; 
    }
    void print ()
    {
        std::cout << " my name is " << name << std::endl ;
    }
private :
    std::string name ;

} ;


int main ( )
{
    std::stirng name ("kylin") ;
    obj obj1 (name) ;
    obj obj2 = obj1 ;
    
    obj1.print () ;
    obj2.print () ;
    
    reutrn 0 ;
    
}