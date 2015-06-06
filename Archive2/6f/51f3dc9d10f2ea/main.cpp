#include <iostream>
#include <type_traits>

namespace A
{
    template< int I = 42 >
    struct X { static void f() { std::cout << I << std::endl; } };
}

namespace B
{
    template< int I = 0 >
    using X = A::X< I >; 
}

int main()
{
    A::X<>::f();
    B::X<>::f();
    static_assert( std::is_same< B::X<>, A::X<0> >::value, "Oops" );
}
