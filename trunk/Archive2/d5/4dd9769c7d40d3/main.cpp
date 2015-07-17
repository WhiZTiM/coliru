#include <iostream>
#include <cstdint>

struct A {
    unsigned int i: 1;
};

int main() {
    A a;
    a.i = 1;
    std::cout << a.i;
    return 0;
}