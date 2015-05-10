#include <cstdlib>
#include <iostream>
#include <vector>
#include <utility>
#include <type_traits>

template<typename T,
    	typename size_type = typename T::size_type,
		typename... Args,
    	typename K = decltype(std::declval<T>()(std::declval<Args>()...)),
		typename U = decltype(std::declval<T>().at(std::declval<Args>()...))
>
auto secure_access(T container, Args... pos) -> std::enable_if_t<std::is_convertible<K, U>::value, K> {
#ifdef NDEBUG
	return container(pos...);
#else
	return container.at(pos...);
#endif
}

struct testmat {
    using size_type = int;
     int operator()(int i, int j) { return 1; }
     int at(int i, int j) { return 2; }
};

int main (int argc, char** argv) {
    testmat A{};
    std::cout << A(3, 4);
    std::cout << secure_access(A, 3, 4);
}
