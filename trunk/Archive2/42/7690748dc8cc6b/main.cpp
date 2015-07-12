#include <iostream>
#include <type_traits>
#include <cstring>

struct has_foo_impl
{
    template <typename> static std::false_type sfinae(...);
    template <typename T> static std::is_same<decltype(std::declval<T>().foo()), void> sfinae(int);
};

template <typename T>
struct has_foo : std::integral_constant<bool, decltype(has_foo_impl::sfinae<T>(0))::value> {};

struct test1
{
    int foo() {}
};

struct test2
{
    void foo() {}
};

struct test3
{
    void bar() {}
};

int main()
{
    std::cout << has_foo<test1>() << '\n';
    std::cout << has_foo<test2>() << '\n';
    std::cout << has_foo<test3>() << '\n';
    return 0;
}