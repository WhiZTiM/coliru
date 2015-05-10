#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>
#include <type_traits>

template<typename T,
    	typename size_type = typename T::size_type,
		typename K = decltype(std::declval<T>()[size_type{}]),
		typename U = decltype(std::declval<T>().at(size_type{}))>
auto secure_access(T container, size_type pos) -> std::common_type_t<K, U> {
#ifdef NDEBUG
	return container[pos];
#else
	return container.at(pos);
#endif
}

int main (int argc, char** argv) {
    std::vector<int>  A(5, 4);
    std::cout << secure_access(A, 3);
}
