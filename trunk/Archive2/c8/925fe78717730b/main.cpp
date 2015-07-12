#include <iostream>
#include <type_traits>
#include <typeinfo>

template<typename T, typename = void>
struct has_foo : std::false_type { };

template<typename T>
struct has_foo<T, decltype(std::declval<T>().foo())> : std::integral_constant<bool, std::is_same<void, decltype(std::declval<T>().foo())>::value> {};

struct T { };
struct U { void foo() { } };
struct V { int foo() {throw;} };

int main() {
    std::cout << has_foo<T>() << '\n';
    std::cout << has_foo<U>() << '\n';
    std::cout << has_foo<V>() << '\n';
}