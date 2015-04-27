#include <cstdlib>
#include <iostream>

std::string foo() {
    return "abcdefghij" + rand() % 5;
}

int main() {
    srand(time(nullptr));
    std::cout << foo();
}