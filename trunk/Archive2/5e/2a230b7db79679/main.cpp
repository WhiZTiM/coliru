#include <iostream>

class Foo 
{
public:
    static int value1;
    static int value2;
};

int Foo::value1 = 42; // some value
int Foo::value2; // no value

int main(void) 
{
    std::cout << Foo::value1 << " " << Foo::value2 << std::endl;    
}