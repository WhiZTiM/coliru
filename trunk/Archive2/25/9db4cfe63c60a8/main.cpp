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
template <typename T>
typename std::enable_if<has_foo_member_function<T>{}>::type foo(T)
{
    std::cout << "has_foo_member_function\n";
}

template <typename T>
typename std::enable_if<!has_foo_member_function<T>{}>::type foo(T)
{
    std::cout << "!has_foo_member_function\n";
}

int main()
{
    foo(A{});
    foo(B{});
}
