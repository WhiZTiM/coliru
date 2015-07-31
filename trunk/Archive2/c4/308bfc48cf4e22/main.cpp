#include <iostream>
    
template <typename X, typename Y = X>
struct has_rebind : std::false_type {};

template <typename X>
struct has_rebind<X, typename X::template rebind<int>> : std::true_type {};

struct A { };
struct B { template <typename > struct rebind { }; };

int main() {
    std::cout << has_rebind<A>::value << std::endl;
    std::cout << has_rebind<B>::value << std::endl;
}