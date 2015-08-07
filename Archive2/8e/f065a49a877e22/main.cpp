#include <iostream>

int* test() {
    int x;
    x++;
    std::cout << x << std::endl;
    return &x;
}


void test3() {
    unsigned long long int m;
    int x;
    std::cout << x << std::endl;
    std::cout << std::hex << m << std::endl;
}

int main() {
    int* y = test();
    test();
    test();
    test();
    test3();
    return 0;
}