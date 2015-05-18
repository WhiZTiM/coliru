#include <iostream>

#include <array>

struct A {
    A(int value) : value(value) {}

    int value;
};    

int main() {
    std::array<A, 1> elements{A(1)};
    
    for (const auto& elem : elements) {
        std::cout << elem.value;
    }    
     
    return 0;
}

