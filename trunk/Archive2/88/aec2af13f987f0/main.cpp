#include <iostream>

struct base
{
    virtual ~base() {}
    virtual void f() = 0;
};

struct derived : base
{
    virtual void f() { std::cout << "derived::f()\n"; }
};

int main()
{
    base * b = 0;
    {
        derived d{};
        b = &d;
    }
    b->f();
}
