#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename X>
void show(X)
{
    std::cout << typeid(X).name() << std::endl;
}

template <typename T>
struct Foo
{
    //static constexpr struct E {} nested {}; // works in gcc and clang
    //static constexpr struct E {T x;} nested {}; // doesn't work in gcc
    //static constexpr enum E {} nested {}; // works in gcc and clang
    //static constexpr enum E { FOO } nested {}; // works in gcc and clang
    //static constexpr struct E { constexpr E() {} constexpr E(const E&) {} T x=T();} nested {}; // works in gcc and clang
    static constexpr struct E { constexpr E() {} constexpr E(const E&) = default; T x=T(); } nested {}; // doesn't work in gcc
};

int main()
{
    Foo<int> x;
    show(x.nested);
}