#include <iostream>

template <typename T, typename U>
struct A
{
    void foo() { std::cout << "A<T,U>\n"; }
};

template <typename U>
struct A<int, U>
{
    void foo() { std::cout << "A<int,U>\n"; }
};

template <typename T, typename U>
struct A<T*, U&>
{
    void foo() { std::cout << "A<T*,U&>\n"; }
};

int main()
{
    A<bool, char> a;
    A<int, float> b;
    A<int*, float&> c;
    
    a.foo();
    b.foo();
    c.foo();
}
