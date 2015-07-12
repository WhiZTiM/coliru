#include <iostream>
#include <type_traits>

template<typename T, typename = void>
struct has_foo : std::false_type { };

template<typename T>
struct has_foo<T, decltype(std::declval<T>().foo())> : std::true_type { };

struct T { };
struct U { void foo() { } };

int main() {
    std::cout << has_foo<T>() << '\n';
    std::cout << has_foo<U>() << '\n';
    return 0;
}