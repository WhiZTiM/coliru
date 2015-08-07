#include <iostream>


int main() {
    int* y;
    std::cout << "PRINTA PORRA" << std::endl;
    std::cout << (&y) << std::endl;
    std::cout << (&y - 1) << std::endl;
    std::cout << (void*)((char*)(&y) - 1) << std::endl;
    std::cout << "PRINTA PORRA" << std::endl;
    return 0;
}