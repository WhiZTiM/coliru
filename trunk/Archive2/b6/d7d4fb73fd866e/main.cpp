#include <cassert>
#include <iostream>
#include <utility>

inline void print_some(const char *) { std::cout << std::endl; }

template<typename T, typename... Ts>
inline void print_some(const char *sep, T first, Ts... rest) {
    std::cout << sep << first;
    print_some(sizeof...(rest) ? ", " : "", rest...);
}

template<typename T, T... Is>
void print_seq(std::integer_sequence<T, Is...>) {
    print_some("", Is...);
}

int main() {
    print_seq(std::make_index_sequence<42>{});
    constexpr auto N = 250; // OK for g++ and clang++  
//  constexpr auto N = 900; // this still works with g++
//  constexpr auto N = 300; // clang++ already bails out at this
    assert(std::make_index_sequence<N>{}.size() == N);
}
