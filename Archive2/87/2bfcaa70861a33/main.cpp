#include <iostream>
#include <string>
#include <vector>

template <std::size_t N>
struct indent
{
    friend auto foo(indent<N>);
    static constexpr std::size_t value = N;
};

struct empty {};

template <std::size_t N, typename T = empty>
struct Y
{
    friend auto foo(indent<N>) { return T{}; }
};

int main()
{
    Y<10, int>{};
    foo(indent<10>{});
    return 0;
}
