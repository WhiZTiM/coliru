#include <iostream>

struct Base
{
    int b;
    virtual void foo(){ std::cout << b << std::endl;}
    Base(int x) : b(x){}
};

struct Derived1 : Base    //not virtual
{
    virtual void foo(){ std::cout << "I am derived 1" << std::endl; }
    Derived1() : Base(1){}
};

struct Derived2 : Base    //not virtual
{
    virtual void foo(){ std::cout << "I am derived 2" << std::endl;}
    Derived2() : Base(2){}
};


struct MultiInheritance : Derived1, Derived2
{
    void bar1()
    {
       Derived1& d1 = *this;
       d1.foo();
    }
    void bar2()
    {
        Derived2& d2 = *this;
        d2.foo();
    }
};

int main()
{
    MultiInheritance m;
    m.bar1();
    m.bar2();
}