#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template<typename T>
using void_t = void;

template<typename F, typename... Args>
using eval_mc = typename F::template apply<Args...>::type;

template<bool Value>
using enable_if = void_t<typename std::enable_if<Value>::type>;

template<typename... Args>
struct is_instantiable_impl
{
    template<template<typename...> class T, typename = void>
    struct type : public std::false_type {};
            
    template<template<typename...> class T>
    struct type<T,void_t<T<Args...>>> : public std::true_type {};
};

template<template<typename...> class T, typename... Args>
using is_instantiable = typename is_instantiable_impl<Args...>::template type<T>;

template<typename T, typename = void>
struct has_type : 
        public std::false_type 
{};

template<typename T>
struct has_type<T, void_t<typename T::type>> :
    public std::true_type 
{};

struct Nothing {};

template<template<typename...> class Template, typename... Args>
struct just
{
    template<template<typename...> class T, typename=void>
    struct impl
    {
        using type = Nothing;  
    };

    template<template<typename...> class T>
    struct impl<T, void_t<typename std::enable_if<is_instantiable<T, Args...>::value>::type>>
    {
        using type = T<Args...>;
    };   

    using type = typename impl<Template>::type;
};

template<template<typename...> class Template, typename... Args>
using just_t = typename just<Template, Args...>::type;

template<typename, typename, typename>
struct curriable_function
{
    using type = void;  
};

template<typename...>
struct non_curriable_function
{
    using type = void;  
};

template<template<typename...> class Function>
struct curry
{
    template<typename... Args>
    struct apply
    {
        using f = just_t<Function, Args...>;

        template<typename F, bool is_function = has_type<F>::value>
        struct call
        {
            using type = typename F::type;
        };

        template<typename F>
        struct call<F, false>
        {
            struct type
            {
                template<typename... Tail>
                struct apply
                {
                    using type = eval_mc<curry, Args..., Tail...>;
                };
            };
        };

        using type = typename call<f>::type;
    };
};


static_assert(is_instantiable<curriable_function, int, int, int>::value, "Not instantiable?");
static_assert(!is_instantiable<curriable_function, int>::value, "Instantiable?");
static_assert(std::is_same<just_t<curriable_function,int>,Nothing>::value, "Instantiable?");
static_assert(!std::is_same<just_t<curriable_function,int, int, int>,Nothing>::value, "Not instantiable?");

using a = curry<curriable_function>;
using b = curry<non_curriable_function>;

static_assert(!std::is_same<eval_mc<a, int>, void>::value, "a(int) was evaluated instead of curried?");
static_assert(std::is_same<eval_mc<a, int, int, int>, void>::value, "a(int, int, int) was curried instead of evaluated?");
static_assert(std::is_same<eval_mc<eval_mc<a,int>, int, int>, void>::value, "a(int)(int,int) was not evaluated?");

int main()
{
}