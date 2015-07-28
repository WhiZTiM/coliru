#include <iostream>
#include <bitset>

int main() {
    bool x = true;
    unsigned int y = (unsigned int)x;
    
    std::cout << "sizeof(x)=" << sizeof(x) << " x=" << std::bitset<4>(x)  << std::endl;
    std::cout << "sizeof(y)=" << sizeof(y) << " y=" << std::bitset<32>(x)  << std::endl;
}
