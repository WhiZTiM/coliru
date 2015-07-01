#include <iostream>

template<class...Ts>
struct Base {
    template<typename T>
    Base(T);
};

template<class... Ts>
struct Derived : Base<Ts...> {
    using Base<Ts...>::Base<int>;
};

int main() { (void)Derived<int, double>(42); }