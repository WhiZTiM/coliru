#include <stdio.h>
#include <string.h>
#include <new>
#include <iostream>
#include <memory>
#include <vector>
//#include <type_traits>

class B{
    public:
    B(){}
    ~B(){}
    B & operator=(const B & b){
        std::cout << " cannot move -> copy " << std::endl; 
        return *this;
    }
    B(const B & v){
        std::cout << " cannot move -> copy " << std::endl;        
    }
    
    B(B && b) = delete;
};


int main()
{
    B b( B{} );
}
