#include <iostream>

struct B
{
    void foo() { std::cout << "B::foo" << std::endl; }
};

struct B2
{
    void foo() { std::cout << "B2::foo" << std::endl; }
};

struct A : public B
{
    void foo() { std::cout << "A::foo" << std::endl; }
};

struct C : public B, public B2
{
};

int main()
{
    A a;
    a.foo(); // calls A::foo
    a.B::foo(); // calls B::foo

    C c;
    c.B2::foo(); // calls B2::foo, needed to disambiguate from B::foo

    return 0;
}
