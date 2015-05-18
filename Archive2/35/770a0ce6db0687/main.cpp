#include <tuple>
#include <utility>
#include <iostream>

void foo(std::string a, std::string b, std::string c) {
    std::cout << a << '|' << b << '|' << c;
}

template <typename, typename> struct passerAux;
template <std::size_t... prevI, std::size_t... followI>
struct passerAux<std::index_sequence<prevI...>, std::index_sequence<followI...>> {
    template <typename... Args>
	static decltype(auto) passer( Args&&... args ) {
		auto tuple = std::forward_as_tuple(std::forward<Args>(args)...);
		return foo( std::forward<std::tuple_element_t<prevI, decltype(tuple)>>(std::get<prevI>(tuple))...,
		            "ModifiedArg",
		            std::forward<std::tuple_element_t<followI+sizeof...(prevI)+1, decltype(tuple)>>(std::get<followI+sizeof...(prevI)+1>(tuple))... );
	}
};

template <typename... Args, std::size_t... indices>
decltype(auto) passer( std::size_t i, std::index_sequence<indices...>, Args&&... args ) {
	void(*lookup[])(Args&&...) {
		passerAux<std::make_index_sequence<indices>, std::make_index_sequence<sizeof...(Args)-indices-1>>::passer...
	};
	return lookup[i](std::forward<Args>(args)...);
}

template <typename... Args>
decltype(auto) passer( std::size_t i, Args&&... args ) {
	return passer(i, std::make_index_sequence<sizeof...(Args)>{}, std::forward<Args>(args)... );
}

int main() {
	passer(0, "A", "B", "C"); std::cout << '\n';
    passer(1, "A", "B", "C"); std::cout << '\n';
    passer(2, "A", "B", "C");
}
