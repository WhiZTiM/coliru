#include <tuple>
#include <utility>
#include <type_traits>
#include <iostream>
template<class...> class typelist {};

template<class F, std::size_t I, class...Tuples>
using apply_result_type = decltype(std::declval<F>()(std::get<I>(std::declval<Tuples>())...));

template<class F, std::size_t...Is, class... Tuples>
typelist<apply_result_type<F, Is, Tuples...>...> compute_result_types(typelist<F, Tuples...>, std::index_sequence<Is...>);

template<class F, std::size_t Size, class... Tuples>
using result_types = decltype(compute_result_types(typelist<F, Tuples...>(), std::make_index_sequence<Size>()));

template <bool...> struct bool_pack;

template <bool... v>
using all_true = std::is_same<bool_pack<true, v...>, bool_pack<v..., true>>;

template<class... Ts>
all_true<!std::is_void<Ts>::value...> do_is_none_void(typelist<Ts...>);

template<class TL>
using has_no_void_in_list = decltype(do_is_none_void(TL()));

template<size_t N, typename Function, typename... Tuples>
constexpr decltype(auto) tuple_for_each_aux(Function&& f, Tuples&&... ts)
{
    return std::forward<Function>(f)(std::get<N>(std::forward<Tuples>(ts))...);
}

template<typename Function, typename... Tuples, std::size_t... Indices, typename = std::enable_if_t<!has_no_void_in_list<result_types<Function, sizeof...(Indices), Tuples...>>::value>>
constexpr void tuple_for_each_aux(Function&& f, std::index_sequence<Indices...>, Tuples&&... ts)
{
    using swallow = int[];
    static_cast<void>(swallow{ 0, (tuple_for_each_aux<Indices>(std::forward<Function>(f), std::forward<Tuples>(ts)...), void(), 0)... });
}

template<typename Function, typename... Tuples, std::size_t... Indices, typename = std::enable_if_t<has_no_void_in_list<result_types<Function, sizeof...(Indices), Tuples...>>::value>>
constexpr decltype(auto) tuple_for_each_aux(Function&& f, std::index_sequence<Indices...>, Tuples&&... ts)
{
    return decltype(std::make_tuple(tuple_for_each_aux<Indices>(std::forward<Function>(f), std::forward<Tuples>(ts)...)...)) { tuple_for_each_aux<Indices>(std::forward<Function>(f), std::forward<Tuples>(ts)...)... };
}

template<typename Function, typename Tuple, typename... Tuples>
constexpr decltype(auto) tuple_for_each(Function&& f, Tuple&& t, Tuples&&... ts)
{
    return tuple_for_each_aux(std::forward<Function>(f), std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{}, std::forward<Tuple>(t), std::forward<Tuples>(ts)...);
}

struct functor
{
    int operator()(int a, int b) { return a + b; }
    double operator()(double a, double b) { return a + b; }
    void operator()(char, char) { return;  }
};

int main()
{
    auto t1 = std::make_tuple(1, 2.0, 'a');
    auto t2 = std::make_tuple(2, 4.0, 'b');
    tuple_for_each(functor{}, t1, t2);
    auto t3 = std::make_tuple(1, 2.0);
    auto t4 = std::make_tuple(2, 4.0);
    auto r = tuple_for_each(functor{}, t3, t4);   
    static_assert(std::is_same<decltype(r), std::tuple<int, double>>{}, "!!!");
    std::cout << std::get<0>(r) << ' ' << std::fixed << std::get<1>(r) << '\n';
    return 0;
}