#include <iostream>
#include <string>
#include <vector>

template<bool Head, bool... Tail>
constexpr bool any = Head || any<Tail...>;

template<bool Head>
constexpr bool any<Head> = Head;

template<bool Head, bool... Tail>
constexpr bool all = Head && all<Tail...>;

template<bool Head>
constexpr bool all<Head> = Head;

int main()
{
    static_assert(any<false, false, true, false>, "");
}
