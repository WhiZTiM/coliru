#include <iostream>
#include <map>

struct A
{
    typedef int type;
};

template<typename T> void foo(T*) { std::cout << "a" << std::endl; }
template<typename T> void foo(typename T::type*) { std::cout << "b" << std::endl; }

template<typename T>
struct identity
{
    typedef T type;
};

template<typename T> void bar(T*) { std::cout << "a" << std::endl; }
template<typename T> void bar(typename identity<T>::type*) { std::cout << "b" << std::endl; }

int main()
{
    //auto f = foo<A>; // ambiguous
    foo<A>(0); // prints "b", as the second overload is more specific

    auto b = bar<A>; // fine
    bar<A>(0); // prints "b", as the second overload is more specific (?)
    b(0); // prints "b"
}