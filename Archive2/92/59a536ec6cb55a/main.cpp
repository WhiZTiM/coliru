#include <iostream>

int* test() {
    int x;
    x++;
    int* px = &x;
    std::cout << x << std::endl;
    return px;
}

void test2() {
    int y = 200;
    std::cout << y << std::endl;
}

void test3(int* y) {
    int z, w;
    //*y = 5;
    std::cout << y << ' ' << std::hex << z << ' ' << w << std::endl;
}

int main() {
    int* y = test();
    test();
    test2();
    test();
    test();
    test3(y);
    return 0;
}