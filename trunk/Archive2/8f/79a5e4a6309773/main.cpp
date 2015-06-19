#include <type_traits>
#include <utility>

template <typename T, typename = void>
struct has_foo_member_function : std::false_type {};

template <typename T>
struct has_foo_member_function<T, decltype(void(std::declval<T&>().foo()))> : std::true_type {};

struct A
{
    void foo() {}
};

struct B
{
};

#include <iostream>
int main()
{
    std::cout << has_foo_member_function<A>::value << std::endl;
    std::cout << has_foo_member_function<B>::value << std::endl;
}
