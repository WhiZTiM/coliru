#include <iostream>

template<typename... Args>
void call_all(Args&&... args) {
    ((std::cout << args() << ' '), ...);
}

template<typename... Args>
void make_args(Args&&... args) {
    call_all(([=]{ return args; })...);
}

int main() {
    auto a = []{ return 10; };
    auto b = []{ return 20; };
    call_all(a, b);
    std::cout << '\n';
    make_args(11, 22, 33);
}