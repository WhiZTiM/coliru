#include <iostream>

int main() {
    int a{}, b{};
    
    true ? a : b = 5;
    std::cout << a << ' ' << b << '\n';
    
    (true ? a : b) = 6;
    std::cout << a << ' ' << b;
}