#include <tuple>
#include <utility>
#include <vector>

struct Msg {
    std::vector<int> values;
};

template <std::size_t... indices, typename Tuple, typename OutputIt>
void copy(std::index_sequence<indices...>, Tuple&& t, OutputIt out) {
	(void)std::initializer_list<int> {
		(*out++ = std::get<indices>(std::forward<Tuple>(t)), 0)...
	};
}

template <typename Tuple, typename OutputIt>
void copy(Tuple&& t, OutputIt out) {
	copy(std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>{}>{},
	     std::forward<Tuple>(t), out);
}

template <typename... Args>
Msg func(Args... args) {
	auto cat = std::tuple_cat(args...);
	Msg m{{sizeof...(args)}};
	copy(cat, std::back_inserter(m.values));
	return m;
}

template <typename... T>
auto foo(T&&... t) {return std::make_tuple(std::forward<T>(t)...);}

#include <iostream>
int main() {
	Msg msg = func(foo(1,2,3), foo(4), foo(5,6,7));
	for (auto i : msg.values)
		std::cout << i << ", ";
}
