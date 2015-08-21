#include <iostream>
#include <type_traits>

template <typename T, typename Enabler = void>
struct maybeChangeType { using type = T; };

template <typename T>
struct Foo
{
    struct Bar {
        using outer = Foo<T>;
    };
};

template <typename T>
auto is_foo_bar_impl(int) -> decltype(typename std::conditional<std::is_same<T, typename T::outer::Bar>::value, std::true_type, std::false_type>::type{});

template <typename T>
std::false_type is_foo_bar_impl(...);

template <typename T>
using is_foo_bar = decltype(is_foo_bar_impl<T>(0));


template <typename T>
struct maybeChangeType<T, std::enable_if_t<is_foo_bar<T>::value>>
{ using type = std::true_type; };

static_assert(is_foo_bar<Foo<int>::Bar>::value, "");

static_assert(std::is_same<std::true_type, maybeChangeType<Foo<int>::Bar>::type>::value, "");
static_assert(std::is_same<int, maybeChangeType<int>::type>::value, "");

int main() {
}