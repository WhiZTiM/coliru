#include <tuple>
#include <type_traits>

template <template <typename...> class Cls>
struct quote {
    template <typename... Args>
    using apply = Cls<Args...>;
};

template <typename... Args>
struct typelist { 
    static constexpr std::size_t size = sizeof...(Args);
};

template <typename F, typename TL>
struct apply;

template <typename F, typename... Args>
struct apply<F, typelist<Args...>> {
    using type = typename F::template apply<Args...>;
};

template <typename F, typename TL>
using apply_t = typename apply<F, TL>::type;

template <typename... Args>
struct concat;

template <typename... Args>
using concat_t = typename concat<Args...>::type;

template <typename... A1, typename... A2, typename... Args>
struct concat<typelist<A1...>, typelist<A2...>, Args...> {
    using type = concat_t<typelist<A1..., A2...>, Args...>;
};

template <typename TL>
struct concat<TL> {
    using type = TL;
};

template<typename A, typename F>
using filter_one = std::conditional_t<F::template apply<A>::value, typelist<A>, typelist<>>;

template<typename F, typename... Args>
concat_t<filter_one<Args, F>...> do_filter(typelist<Args...>);

template <typename TL, typename F>
using filter_t = decltype(do_filter<F>(TL()));

template <typename F>
struct not_ {
    template <typename Arg>
    using apply = std::conditional_t<F::template apply<Arg>::value,
                                     std::false_type,
                                     std::true_type>;
};

template <typename TL, typename F>
struct partition {
    using type = concat_t<filter_t<TL, F>,
                          filter_t<TL, not_<F>>
                          >;
};
template <typename TL, typename F>
using partition_t = typename partition<TL, F>::type;


template<class T, std::size_t OldIndex, std::size_t NewIndex>
struct index_map_leaf {
    using type = T;
    static constexpr std::size_t old_index = OldIndex;
    static constexpr std::size_t new_index = NewIndex;
};

template<class... Leaves>
struct index_map : Leaves... {};

// Given a metafunction, returns a metafunction that applies the metafunction to
// its argument's nested typedef type.
template<class F>
struct project_type {
    template<class... Args>
    using apply = typename F::template apply<typename Args::type...>;
};

template<class... Ts, std::size_t... Is>
typelist<index_map_leaf<Ts, Is, 0>...> do_build_old_indices(typelist<Ts...>, std::index_sequence<Is...>);

template<class... Ts, std::size_t... Is, std::size_t...Js>
typelist<index_map_leaf<Ts, Is, Js>...> do_build_new_indices(typelist<index_map_leaf<Ts, Is, 0>...>, std::index_sequence<Js...>);

template<class TL>
using build_old_indices = decltype(do_build_old_indices(TL(), std::make_index_sequence<TL::size>()));

template<class TL>
using build_new_indices = decltype(do_build_new_indices(TL(), std::make_index_sequence<TL::size>()));

template<class TL, class F>
using make_index_map = apply_t<quote<index_map>, build_new_indices<partition_t<build_old_indices<TL>, project_type<F>>>>;

template<std::size_t OldIndex, std::size_t NewIndex, class T>
index_map_leaf<T, OldIndex, NewIndex> do_convert_index(index_map_leaf<T, OldIndex, NewIndex>);

template<std::size_t OldIndex, class IndexMap>
using converted_index_t = decltype(do_convert_index<OldIndex>(IndexMap()));

template<template<class...> class T, class... Args>
typelist<Args...> do_as_typelist(typelist<T<Args...>>);

template<class T>
using as_typelist = decltype(do_as_typelist(typelist<T>()));

template<class Tuple, class F>
struct tuple_partitioner {
    using map_type = make_index_map<as_typelist<Tuple>, F>;
    using reordered_tuple_type = apply_t<project_type<quote<std::tuple>>, as_typelist<map_type>>;
    template<std::size_t OldIndex>
    using new_index_for = std::integral_constant<std::size_t, converted_index_t<OldIndex, map_type>::new_index>;
};

int main(){
    using original_tuple = std::tuple<int, double, long, float, short>;
    using f = quote<std::is_integral>;
    using partitioner = tuple_partitioner<original_tuple, f>;
    
    static_assert(partitioner::new_index_for<0>() == 0, "!");
    static_assert(partitioner::new_index_for<1>() == 3, "!");
    static_assert(partitioner::new_index_for<2>() == 1, "!");
    static_assert(partitioner::new_index_for<3>() == 4, "!");
    static_assert(partitioner::new_index_for<4>() == 2, "!");
    static_assert(std::is_same<partitioner::reordered_tuple_type, std::tuple<int, long, short, double, float>>{}, "!");
}
    