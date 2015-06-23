#include <iostream>

struct A{ void foo(){ std::cout << "A()" << std::endl; }; };

struct B : A{ void foo(){ std::cout << "A()" << std::endl; }; };

int main ()
{
    A a;
    B& c = static_cast<B&>(a);
    c.foo();
}
