#include <iostream>

void test() {
    int x;
    int* p = &x;
    x++;
    std::cout << x << std::endl;
}

void test3() {
    int* p;
    std::cout << p << std::endl;
    *p = 200;
}

int main() {
    test();
    test();
    test();
    test();
    test3();
    test();
    return 0;
}