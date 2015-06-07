#include <type_traits>
#include <tuple>
#include <string>

struct space {};
template<typename, typename=void> struct spacer;

template<template<typename...> class T>
struct spacer<T<>> { using type = T<>; };

template<template<typename...> class T,typename T1, typename... Ts>
struct spacer<T<T1,Ts...>> : spacer<T<T1,Ts...>, std::make_index_sequence<2*sizeof...(Ts)+1>> {};

template<template<typename...> class T,typename... Ts, std::size_t... Ns>
struct spacer<T<Ts...>, std::index_sequence<Ns...>>
{
    using tuple = std::tuple<Ts...>;
    using type = T<std::conditional_t<(Ns%2)==0,std::tuple_element_t<Ns/2,tuple>,space>...>;
};

template<typename T> using spacer_t = typename spacer<T>::type;

template<typename...> struct childrenListType {};

int main()
{
    static_assert( std::is_same< spacer_t<childrenListType<>>,childrenListType<> >::value, "Oops" );
    static_assert( std::is_same< spacer_t<childrenListType<std::string>>,childrenListType<std::string> >::value, "Oops" );

    using source = childrenListType<std::string, std::string, std::string, std::string>;
    using expected = childrenListType<std::string, space, std::string, space, std::string, space, std::string>;
    using spaced = spacer_t<source>;

    static_assert( std::is_same< spaced, expected >::value, "Oops" );
}
