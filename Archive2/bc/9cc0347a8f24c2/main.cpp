#include <iostream>

template<class...Ts>
struct Base {
    Base();
};

template<class... Ts>
Base<Ts...>::Base<Ts...>(){ std::cout << "wut?\n"; }

int main() { (void)Base<int, double>(); }