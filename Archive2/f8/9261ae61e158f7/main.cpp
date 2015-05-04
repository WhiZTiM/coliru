#include <iostream>

template<typename T> struct A { using type = T; };

template<int I> struct B { int m = 7; };

struct D : B<1> { int m = 3; };

int main()
{
    D d;
    std::cout << d.m << '\n';
    std::cout << d.B<1>::m << '\n'; // B found as the injected-class-name in D
    std::cout << d.A<B<1>>::type::m << '\n'; // A found in the global scope
                                             // (B as well here, but for a different reason)
}
