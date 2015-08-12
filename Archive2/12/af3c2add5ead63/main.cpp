#include <iostream>

using MemberFunctionType = void () const volatile;

struct A
{    
    virtual MemberFunctionType foo = 0;
};

struct B : A
{
    void foo() const volatile override
    {
        std::cout << 1;
    }
};

int main()
{
    B b;
    A* a = &b;
    a->foo();
}
