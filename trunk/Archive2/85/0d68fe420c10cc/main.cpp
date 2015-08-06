#include <iostream>
#include <type_traits>


template <typename T>
struct Foo
{
};

struct Bar : public Foo<int>
{
};

namespace impl {

    template<template<class...> class B, class... Ts>
    constexpr bool is_template_base_of(const B<Ts...>*)
    {
        return true;
    }

    constexpr bool is_template_base_of(...)
    {
        return true;
    }

}

template<template<class...> class BaseT, class MaybeDerivedT>
using is_template_base_of
= std::integral_constant<bool,
    impl::is_template_base_of<BaseT>((MaybeDerivedT*)0)>;


int main()
{
    std::cout << is_template_base_of<Foo, Bar>::value << std::endl;
}
