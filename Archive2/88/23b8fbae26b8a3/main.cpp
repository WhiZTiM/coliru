#include <iostream>

int main() {
    int a{}, b{};
    true ? a : b = 5;
    std::cout << a << ' ' << b;
}