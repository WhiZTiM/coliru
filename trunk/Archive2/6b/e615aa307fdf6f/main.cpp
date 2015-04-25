#include <type_traits>
#include <typeinfo>
#include <iostream>

namespace detail
{
    template<typename...>
    using void_t = void;
    
    template<template<typename...> class...>
    using void_template = void;
    
    template<typename T, typename=void>
    struct has_apply_type : std::false_type {};
    
    template<typename T>
    struct has_apply_type<T, void_t<typename T::apply>> : std::true_type {};
    
    template<typename T, typename=void>
    struct has_apply_template : std::false_type {};
    
    template<typename T>
    struct has_apply_template<T, void_template<T::template apply>> : std::true_type {};
}

template<typename T>
using is_metafunction_class = std::integral_constant<bool, detail::has_apply_type<T>::value ||
                                                           detail::has_apply_template<T>::value>;
//Examples:
struct metafunction_class
{
    template<typename... Args>
    struct apply
    {
        using type = detail::void_t<Args...>;  
    };
};

struct nullary_metafunction_class
{
    struct apply
    {
        using type = void;
    };
};

struct nullary_metafunction
{
    using type = void;   
};

static_assert(is_metafunction_class<metafunction_class>::value,"");
static_assert(is_metafunction_class<nullary_metafunction_class>::value,"");
static_assert(is_metafunction_class<nullary_metafunction>::value,"");

int main(){}
