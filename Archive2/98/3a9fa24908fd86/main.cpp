#include <iostream>



int main() {
    const int x = 42;
    const int &r = x;
    const_cast<int &>(x)++;
    std::cout << "x= " << x << std::endl;
    std::cout << "r= " << r << std::endl;
}