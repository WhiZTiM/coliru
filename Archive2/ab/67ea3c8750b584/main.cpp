#include <vector>
#include <iostream>

int func() { return 123; }

template<typename Type>
Type default_constructor() { return Type(); }

template <typename T, T(INIT)() = default_constructor<T>> struct Foo
{
    T value = INIT();
};

int main() {
    Foo<int, func> x;
    Foo<int> y;
    std::cout << x.value << '\n';
    std::cout << y.value;
}