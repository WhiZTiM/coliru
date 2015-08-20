#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>
#include <iostream>

template<typename F, typename Tuple, size_t ...S >
auto apply_tuple_impl(F&& fn, Tuple&& t, std::index_sequence<S...>)
{
    return std::forward<F>(fn)(std::get<S>(std::forward<Tuple>(t))...);
}

template<typename F, typename Tuple>
auto apply_from_tuple(F&& fn, Tuple&& t)
{
	std::size_t constexpr tSize
		= std::tuple_size<typename std::remove_reference<Tuple>::type>::value;

	return apply_tuple_impl(std::forward<F>(fn),
	                        std::forward<Tuple>(t),
	                        std::make_index_sequence<tSize>());
}

int do_sum(int a, int b) 
{
	return a + b;
}

int main()
{
	int sum = apply_from_tuple(do_sum, std::make_tuple(10, 20));
    std::cout << sum << std::endl;
}