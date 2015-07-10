#include <iostream>

class A
{
public:
    virtual void foo() const {std::cout << "A\n";}
};

class B: public A
{
public:
    virtual void foo() const {std::cout << "B\n";}
};

class C: public A
{
public:
    virtual void foo() {std::cout << "C\n";}
};

int main()
{
    const A* bar = new B;
    const A* baz = new C;
    bar->foo(); //Override
    baz->foo(); //Hiding
}
