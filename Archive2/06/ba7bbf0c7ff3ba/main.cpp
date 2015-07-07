
#include <iostream>

class Car
{
public:
    int x;
    std::string str;
};


template<class U>
char[2] foo( decltype(U::x)* )
{
}


int main ( )
{
    
    int Car::*pX = &Car::x;
    
    auto Car::*pStr = &Car::str;
    
    Car c1;
    c1.*pX = 12;
    

    
    
    std::cout << c1.*pX;
}