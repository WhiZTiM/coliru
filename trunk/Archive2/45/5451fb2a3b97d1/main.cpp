#include <type_traits>

template <template <typename> class>
struct X {};

template<typename>
struct Y {};

template<typename T>
using Z = Y<T>;

int main()
{
    static_assert( std::is_same< Y<int>, Z<int> >::value, "Oops" );
    static_assert( ! std::is_same< X<Y>, X<Z> >::value, "Oops" );
}