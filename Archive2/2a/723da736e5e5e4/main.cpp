#include <iostream>
#include <type_traits>
 
struct A {
    int m;
};

struct D : public A { };

struct B {
    virtual void foo();
};
 
struct C : B {};
 
int main()
{
    std::cout << std::boolalpha;
    std::cout << std::is_polymorphic<A>::value << '\n';
    std::cout << std::is_polymorphic<B>::value << '\n';
    std::cout << std::is_polymorphic<C>::value << '\n';
    std::cout << std::is_polymorphic<D>::value << '\n';
}