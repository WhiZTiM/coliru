template<typename T>
struct base
{
    T t;
    base() : t() {}
};

#include <type_traits>

template<typename T>
struct foo
{
    base<T> t;
    constexpr foo() {}
};

int main()
{
    static_assert(std::is_default_constructible<foo<int&>>{}, "!");
}