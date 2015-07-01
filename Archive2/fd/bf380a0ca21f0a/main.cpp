#include <iostream>

template<class...Ts>
struct Base {
    Base<Ts...>() { std::cout << "wut?\n"; }
};

int main() { (void)Base<int, double>(); }