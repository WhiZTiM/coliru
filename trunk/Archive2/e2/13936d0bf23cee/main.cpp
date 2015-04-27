#include <cstdlib>
#include <iostream>
#include <string>

std::string foo() {
    return "abcdefghij" + rand() % 5;
}

int main() {
    std::srand(std::time(nullptr));
    std::cout << foo();
}