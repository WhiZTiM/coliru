#include <iostream>


class A{
        
    public :
    
    A(){}
    
    A(const std::string& s){}
    
    A& operator = (const std::string& s){
        return *this;    
    }
};


int main (void){

A a;
a = "abc";


return 0;    
}