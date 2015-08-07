#include <iostream>

int* test() {
    int x;
    x++;
    std::cout << x << std::endl;
    return &x;
}

void test3(int* y) {
    int x;
    std::cout << x << std::endl;
    std::cout << y << std::endl;
}

int main() {
    int* y;
    y = (int*)((char*)(&y) - sizeof(int*) - sizeof(void*) - 8 - sizeof(int));
    *y = 10000;
    test();
    test();
    test();
    test3(y);
    return 0;
}