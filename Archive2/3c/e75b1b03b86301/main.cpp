#include <iostream>

void foo(int) {}

int main() {
    int i = 0;
    foo(i++);
    std::cout << i;
}