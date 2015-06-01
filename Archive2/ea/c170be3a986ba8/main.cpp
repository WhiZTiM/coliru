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

template <typename Indent, typename T = empty>
struct Y
{
    friend auto foo(indent<Indent::value>) { return T{}; }
};

int main()
{
    Y<indent<10>, int>{};
    foo(indent<10>{});
    return 0;
}
