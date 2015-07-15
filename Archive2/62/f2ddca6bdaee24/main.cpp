#include <iostream>

struct A
{
    int a;
    int b;
    A() : a(10) { std::cout << "default ctor" << std::endl;}
    ~A(){ }
    A(const A&){ std::cout << "copy ctor" << std::endl; }
    A(const A&&){ std::cout << "move ctor" << std::endl; }
};

A init()
{
    A a;
    a.b = 20;
    return a;
}

int main()
{
    A a = init();
    std::cout << a.b << std::endl;
}
