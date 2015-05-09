#include <utility>
#include <type_traits>

template<std::size_t...> struct seq{ using type = seq; };

template<class S1, class S2> struct concat;

template<std::size_t... I1, std::size_t... I2>
struct concat<seq<I1...>, seq<I2...>>
  : seq<I1..., I2...>{};

template<template<std::size_t> class pred, std::size_t B, std::size_t N>
struct gen_seq : concat<typename gen_seq<pred, B, N/2>::type, typename gen_seq<pred, B + N/2, N - N/2>::type>::type {};

template<template<std::size_t> class pred, std::size_t B> struct gen_seq<pred, B, 0> : std::conditional<pred<B>::value,seq<B>,seq<>>::type {};
template<template<std::size_t> class pred, std::size_t B> struct gen_seq<pred, B, 1> : std::conditional<pred<B+1>::value,seq<B+1>,seq<>>::type {};

template<std::size_t N>
struct MyData
{
    std::size_t values[N];

    static constexpr std::size_t size()
    { return N; }
};

template<std::size_t... Is>
constexpr MyData<sizeof...(Is)> MyGen(seq<Is...>)
{
    return {{ Is... }};
}

template<template<std::size_t> class pred, std::size_t N>
constexpr auto MyGen() -> decltype(MyGen(typename gen_seq<pred,0,N>::type()))
{
    return MyGen(gen_seq<pred,0,N>());
}

template< std::size_t N > struct my_pred : std::integral_constant< bool, N % 3 == 0 > {};

int main()
{
    auto data = MyGen<my_pred, 10>();
    static_assert( data.size() == 3, "Oops" );

    auto data2 = MyGen<my_pred, 10000>();
    static_assert( data2.size() == 3333, "Oops" );
}
