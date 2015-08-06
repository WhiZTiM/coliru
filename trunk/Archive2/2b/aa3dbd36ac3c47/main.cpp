#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <tuple>

template <typename X>
void show(X)
{
    std::cout << typeid(X).name() << std::endl;
}

template<class... Ts>
class type_list {};

template<class... Ts>
constexpr auto make_list(Ts...)
{
    return type_list<Ts...>();
}

template <typename T>
struct Foo
{
    static constexpr auto nested = type_list<float, short>();
    using G = decltype(make_list(nested));
};

int main()
{
    Foo<int> x;
    show(x.nested);
    Foo<int>::G y;
    show(y);
}