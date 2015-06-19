#include <iostream>

template<typename... Args>
void fancy(Args... args) {
    std::cout << "The squared sum of ";
    ((std::cout << args << ' '), ...);
    std::cout << "is ";
    auto x = ((args * args) + ...);
    std::cout << x << '\n';
}

int main() {
    fancy(2, 4, 6, 8);
}
