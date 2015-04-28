#include <iostream>
#include <utility>

struct A
{
    int x = 1;
};
struct B
{
    int y = 2;
};
struct C
{
    int x = 3;
    int y = 4;
};

namespace detail {

template<typename T, int T::*Mem>
int f(T const& t, bool)
{
    return t.*Mem;
}

}

template<typename T>
auto f(T const& t)
    -> decltype(detail::f<T, &T::x>(t, true))
{
    return detail::f<T, &T::x>(t, true);
}

template<typename T>
auto f(T const& t)
    -> decltype(detail::f<T, &T::y>(t, 1))
{
    return detail::f<T, &T::y>(t, 1);
}

int main()
{
    A a;
    std::cout << f(a) << std::endl;
    B b;
    std::cout << f(b) << std::endl;
    C c;
    std::cout << f(c) << std::endl;
}
