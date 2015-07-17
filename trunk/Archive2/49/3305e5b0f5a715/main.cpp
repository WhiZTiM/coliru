#include <iostream>
#include <cstdint>

struct A {
    unsigned int i: 2;
};

int main() {
    A a;
    a.i = 3;
    std::cout << a.i;
    return 0;
}