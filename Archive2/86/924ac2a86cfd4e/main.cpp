#include <iostream>

int func() { return 123; }

template<typename Type, typename... Args>
Type constructor(Args... args) { 
    return Type(std::forward<Args>(args)...);
}

template <typename T, T(INIT)() = constructor<T>> struct Foo
{
    T value = INIT();
};

int main() {
    Foo<int, func> x;
    Foo<int> y;
    std::cout << x.value << '\n';
    std::cout << y.value;
}