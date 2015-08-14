#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>
#include <sstream>

    template <typename T> struct ArrayAs;

    template <typename T, typename U, std::size_t N>
    struct ArrayAs<T(std::array<U,N>)> {};

    template<class T>
    struct to_array;
    template<class T, size_t N>
    struct to_array< T[N] > { using type = std::array<T, N>; };
    template<class T>
    using arr = typename to_array<T>::type;

struct foo {};

int main() {
    ArrayAs< foo( arr<int[3]> ) > bob;
    (void)bob;
}
