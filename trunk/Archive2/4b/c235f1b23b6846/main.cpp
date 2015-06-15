#include <iostream>
int main() {
    try {
        throw nullptr;
        std::cout << "impossible.\n";
    } catch (std::nullptr_t& t) {
        std::cout << "gotcha\n";
    }
    std::cout << "fini\n";
    return 0;
}