#include <iostream>

struct A
{
    void foo() const{ }
};

const A a;
A b;

int main()
{
    a.foo();
    b.foo();
}