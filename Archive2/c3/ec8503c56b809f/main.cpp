#include <vector>
#include <iostream>

namespace detail {
    
template<template<typename...> class Container, typename Init, int... Indices>
Container<Init> repeat(Init const& init, std::integer_sequence<int, Indices...>)
{ return Container<Init> { (static_cast<void>(Indices), init)... }; }

} // detail

template<int N, template<typename...> class Container = std::vector, typename Init>
Container<Init> repeat(Init const& init)
{ return detail::repeat<Container>(init, std::make_integer_sequence<int, N> {}); }

int main()
{
    auto v = repeat<7>(4);
    for(auto& e: v) std::cout << e << '\n';
}
