#include <iostream>


int main() {
    int* y = new int;
    delete y;
    int* x = new int;
    *y = 1000;
    std::cout << *x << std::endl;
    return 0;
}