#include <iostream>
#include <type_traits>

struct foo {
    constexpr static int X = 5;
};

struct bar { };

template <typename T>
struct has_x {
    template <typename U>
    static std::true_type
    test(decltype(U::X)*);
    
    template <typename>
    static std::false_type
    test(...);
    
    constexpr static bool value = decltype(test<T>(nullptr))::value;
};

template <typename T, bool = has_x<T>::value>
struct get_x;

template <typename T>
struct get_x<T, true> {
    constexpr static int value = T::X;
};

template <typename T>
struct get_x<T, false> {
    constexpr static int value = 0;
};

int
main() {
    std::cout << get_x<foo>::value << '\n';
    std::cout << get_x<bar>::value << '\n';
}
