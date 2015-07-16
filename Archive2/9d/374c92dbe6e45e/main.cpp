#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int a = 1, b = 2;
    for (auto& i : {&a, &b}) *i = 0;
    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';
}