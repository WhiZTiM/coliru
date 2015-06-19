#include <iostream>

template <typename T>
struct A;

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
    // A<long> c; // Błąd!
    
    a.foo();
    b.foo();
}
