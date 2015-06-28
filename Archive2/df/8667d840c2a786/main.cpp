#include <iostream>

struct A
{
    const int a = 1;
    virtual void foo() = 0;
};

struct B : A{ virtual void foo();};

void A::foo(){ std::cout << "afoo" << std::endl; }
void B::foo(){ std::cout << "bfoo" << std::endl; }

int main(int argc, char ** argv)
{
    B b;
    b.foo();
    b.A::foo();
}

