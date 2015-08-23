#include <iostream>
#include <string>
#include <vector>

template<bool Head, bool... Tail>
struct any {
    static constexpr bool value = Head || any<Tail...>::value;
};

template<bool Head>
struct any<Head> {
    static constexpr bool value = Head;
};

template<bool Head, bool... Tail>
struct all {
    static constexpr bool value = Head && any<Tail...>::value;
};

template<bool Head>
struct all<Head> {
    static constexpr bool value = Head;
};

int main()
{
    static_assert(any<false, false, true, false>::value, "");
}
