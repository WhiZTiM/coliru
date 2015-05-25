#include <iostream>
#include <tuple>
#include <utility>

template <std::size_t N>
struct foo
{ };

namespace detail
{
    template <std::size_t... Ns>
    auto constexpr make_foople(std::index_sequence<Ns...> const)
    { return std::make_tuple(foo<Ns>{}...); }
}

template <std::size_t N>
auto constexpr make_foople()
{ return detail::make_foople(std::make_index_sequence<N>{}); }

template <typename T>
void show_type()
{ static_assert((T*)0, "look at T"); }

int main()
{
    auto constexpr foople(make_foople<5>());
    show_type<decltype(foople)>();
}
