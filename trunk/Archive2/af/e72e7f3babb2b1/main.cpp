#include <iostream>

template<typename... Ts>
auto multiply_incremented(Ts... ts) {
    return ((1 + ts) * ...);
}

int main() {
    std::cout << multiply_incremented(1, 5, 7); //2 * 6 * 8 = 96   
}