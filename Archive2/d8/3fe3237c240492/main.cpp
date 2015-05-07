#include <iostream>

void foo(int, int = 2);

void foo(int i = 1, int j) {
    std::cout << i << ' ' << j;
}

int main() {
    foo();   
}