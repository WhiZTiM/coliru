#include <iostream>
#include <type_traits>

template <typename T>
constexpr void show(T t)
{
    auto same = std::is_same<T, decltype(t)>::value;
    std::cout << "They are " << (same ? "the same" : " NOT the same") << std::endl;
}

template <typename T>
struct Foo
{
    static constexpr struct { T a; } nested {};
};

int main()
{
    Foo<int> x;
    show(x.nested);
}