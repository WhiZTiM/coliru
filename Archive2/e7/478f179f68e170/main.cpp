#include <iostream>

int main() {
    auto add5 = [] (int y) { return 5 + y; };
    std::cout << add5(2) << '\n';
    return 0;
}