#include <iostream>
#include <type_traits>

template <typename T>
void show(T t)
{
    auto same = std::is_same<T, decltype(t)>::value;
    std::cout << "They are " << (same ? "the same" : " NOT the same") << std::endl;
}

struct Foo
{
    static constexpr struct { int a; } nested {};
};

int main()
{
    show(Foo::nested);
}