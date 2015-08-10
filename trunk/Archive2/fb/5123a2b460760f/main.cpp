#include <iostream>
#include <type_traits>
#include <utility>

template <char... C>
struct StringType
{
};

namespace impl
{
    template <size_t S, size_t... indices>
    constexpr auto make_string(const char (&s)[S], std::index_sequence<indices...>)
    {
        return StringType<s[indices]...>();
    }
}

template <size_t S>
constexpr auto make_string(const char (&s)[S])
{
    return StringType<s[0]>();
    //return impl::make_string(s, std::make_index_sequence<S>());
}

int main()
{
    constexpr auto s = make_string("hello");
}
