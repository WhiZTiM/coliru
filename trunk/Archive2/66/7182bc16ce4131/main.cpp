#include <iostream>

struct base
{
    virtual ~base() {}
    virtual void f() = 0;
};

struct derived : base
{
    ~derived() { std::cout << "~derived()" << std::endl; }
    virtual void f() { std::cout << "derived::f()" << std::endl; }
    int fake;
};

int main()
{
    base * b = 0;
    {
        derived d;
        b = &d;
        b->f(); //ok
    }
    b->f(); //UB
}
