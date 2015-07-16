#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

int main() {
    int a = 1, b = 2;
    for (auto& i : {std::ref(a), std::ref(b)}) 
        i.get() = 0;
    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';
}