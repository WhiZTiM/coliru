#include <iostream>

int main() {
    float foo{0.1f};
    if (foo == 0.1f)
        std::cout << "A";
    else
        std::cout << "B";
}