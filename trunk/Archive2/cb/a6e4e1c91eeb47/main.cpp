#include <iostream>


int main() {
    int* y = new int(1000);
    delete y;
    int* x = new int;
    std::cout << *x << std::endl;
    return 0;
}