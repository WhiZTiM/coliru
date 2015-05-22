#include <iostream>
#include <typeinfo>

struct T { };

struct U : T { };

int main()
{
    U u;
    
    T& t = u;
    
    std::cout << (typeid(t) == typeid(T));
}
