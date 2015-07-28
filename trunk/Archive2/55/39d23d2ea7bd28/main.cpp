#include <iostream>
#include <bitset>

int main() {
    int a = -58, b = a>>3, c = -315;

    std::cout << "a = " << std::bitset<16>(a)  << std::endl;
    std::cout << "b = " << std::bitset<8>(b)  << std::endl;
    std::cout << "c = " << std::bitset<16>(c) << std::endl;
}
