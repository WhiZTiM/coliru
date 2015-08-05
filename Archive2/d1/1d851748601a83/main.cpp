#include <iostream>
#include <type_traits>
#include <typeinfo>

template <typename X>
void show(X)
{
    std::cout << typeid(X).name() << std::endl;
}


struct E { 
    int x; 
    constexpr E(int t) noexcept : x{t} {} 
    constexpr E() noexcept : x{55} {} 
};

template <typename T>
struct Foo
{
    //static constexpr struct E {} nested {}; // works in gcc and clang
    static constexpr E nested{5}; // doesn't work in gcc
};

int main()
{
 //   Foo<int> x;
    //show(Foo<int>::nested);
    int test = Foo<int>::nested.x;
    //std::cout << typeid(Foo<int>::nested).name() << std::endl;
    std::cout << test; 
}