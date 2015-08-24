#include <iostream>
#include <string>
#include <memory>

struct Base
{
    virtual void foo() = 0;
    virtual void bar() = 0;
    void cb()
    {
        foo();
        bar();
    }
    
    int id;
};

struct Derived : Base
{
    virtual void foo() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
    virtual void bar() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
};

int main()
{
    std::unique_ptr<Base> ptr = std::unique_ptr<Base>(new Derived());
    ptr->cb();
}