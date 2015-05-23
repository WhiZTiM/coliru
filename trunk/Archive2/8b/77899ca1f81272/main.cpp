#include <iostream>

template <typename... >
using void_t = void;

template <typename T, typename = void>
struct is_const_callable_method : std::false_type { };

template <typename T>
struct is_const_callable_method<T, void_t<
    decltype(std::declval<const T&>().method())
    > > : std::true_type { };
    
struct A {
    void method() const { }
};

struct B {
    void method() { }
};

int main() 
{
    std::cout << is_const_callable_method<A>::value << std::endl;
    std::cout << is_const_callable_method<B>::value << std::endl;
}