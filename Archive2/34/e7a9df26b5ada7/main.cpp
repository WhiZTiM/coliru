#include <iostream>
#include <cstring>

int* test() {
    int x;
    x++;
    std::cout << x << std::endl;
    size_t y = (size_t)&x;
    return (int*)y;
}

void test3(int* y) {
    int x;
    std::cout << x << std::endl;
    std::cout << std::hex << y << std::endl;
}

int main() {
    int* y = test();
    test();
    test();
    test();
    test3(y);
    return 0;
}