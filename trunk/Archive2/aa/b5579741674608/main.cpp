#include <iostream>

void test() {
    int* x = new int;
    *x++;
    std::cout << *x; 
    //delete x;
}

void test2() {
    int* x = new int;
    *x = 200;
    std::cout << *x;
    //delete x;
}

int main() {
    test2();
    test();
    test();
    return 0;
}