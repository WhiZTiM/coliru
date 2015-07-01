#include <iostream>

template<class...Ts>
struct Base {
    template<typename T>
    Base();
};

template<class... Ts>
struct Derived : Base<Ts...> {
    using Base<Ts...>::Base<int>;
};

int main() { (void)Derived<int, double>(); }