#include <iostream>

struct A
{
    const int a;
    virtual void foo() = 0;
};

struct B : A{ };

void A::foo(){ std::cout << "foo" << std::endl; }

int main(int argc, char ** argv)
{
    B b;
    b.foo();
}

