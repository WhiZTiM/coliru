#include <iostream>
#include <string>
#include <utility>

class A {};

void foo(const A&  a) { std::cout << "Reference" << std::endl; }

void foo(      A&& a) { std::cout << "Move" << std::endl; }

template <typename T, typename = decltype(foo(std::forward<T>(std::declval<T&>())))>
void bar(T&& a)
{
    //Other things, which treat "a" as a const reference
    foo(std::forward<T>(a));
}

void bar(std::string a) 
{
    std::cout << a << std::endl;
}

int main() {
    A a;
    bar(a);
    bar(A());
    bar("abc"); // not ambiguous
}