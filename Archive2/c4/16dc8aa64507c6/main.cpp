#include <iostream>

int f() {
    std::cout << "f";
    return 1;
}

int g() {
    std::cout << "g";
    return 2;
}

int main() {
    std::cout << f() << g() << '\n';   
}