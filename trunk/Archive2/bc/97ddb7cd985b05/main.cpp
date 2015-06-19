#include <iostream>

template <typename T>
struct A
{
    void foo() { std::cout << "A<T>\n"; }
};

template <>
struct A<int>
{
    void foo() { std::cout << "A<int>\n"; }
};

template <>
struct A<bool>
{
    void foo() { std::cout << "A<bool>\n"; }
};

int main()
{
    A<int> a;
    A<bool> b;
    A<long> c;
    
    a.foo();
    b.foo();
    c.foo();
}
