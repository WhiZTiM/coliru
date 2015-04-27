#include <iostream>

int main() {
    float foo{0.1};
    if (foo == 0.1)
        std::cout << "A";
    else
        std::cout << "B";
}