#include <type_traits>
#include <utility>

template <typename...>
using void_t = void;

template <typename T, typename = void>
struct has_nested_type : std::false_type {};

template <typename T>
struct has_nested_type<T, void_t<typename T::type>> : std::true_type {};

struct A
{
    using type = int;
};

struct B
{
};

#include <iostream>
int main()
{
    std::cout << has_nested_type<A>::value << std::endl;
    std::cout << has_nested_type<B>::value << std::endl;
}
