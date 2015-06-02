#include <iostream>
#include <string>
#include <vector>

template <std::size_t N>
struct X
{
    friend auto foo(X<N>);
};

struct empty {};

template <std::size_t N, typename T = empty>
struct Y
{
    static int const force_instantiation = sizeof(X<N>);
    friend auto foo(X<N>) { return T{}; }
};

int main()
{
    Y<10, int> y;
    foo(X<10>{});
    return 0;
}
