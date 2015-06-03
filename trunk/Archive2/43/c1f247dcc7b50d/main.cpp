#include <iostream>

struct A{ A(){ std::cout << "A()" << std::endl; } };

void foo()
{
    static A a;
}

int main()
{
    foo();
    foo();
}