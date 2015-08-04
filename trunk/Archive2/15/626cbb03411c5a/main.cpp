#include <iostream>
#include <type_traits>

template <typename T, typename X>
constexpr void show(T, X)
{
    auto same = std::is_same<typename T::bar, X>::value;
    std::cout << "They are " << (same ? "the same" : " NOT the same") << std::endl;
}

template <typename T>
struct Foo
{
    static constexpr struct { T a; } nested {};
    using bar = decltype(nested);
};

int main()
{
    Foo<int> x;
    show(x, x.nested);
}