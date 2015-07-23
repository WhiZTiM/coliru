#include <iostream>
#include <string>
#include <vector>

struct Base
{
    virtual void foo() const { std::cout << "Base.foo()" << std::endl; }
};

struct Derived : public Base
{
    virtual void foo() const { std::cout << "Derived.foo()" << std::endl; }
};

void printer(const Base& object)
{
    object.foo();
}

int main()
{
    Base b;
    Derived d;
    
    printer(b);
    printer(d);
}
