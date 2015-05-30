#include <iostream>

struct Tbits {
    uint8_t b0:1;
    uint8_t b1:1;
};

struct Tbytes {
    uint8_t byte0;
};

union Tmixes {
    Tbits as_bits;
    Tbytes as_bytes;
};

int main() {
    Tmixes test;
    std::cout << "Check 0-initialized :";
    std::cout << static_cast<unsigned>(test.as_bytes.byte0) <<std::endl;
    
    std::cout << "Set bit 1" << std::endl;
    test.as_bits.b1 = 1;
    
    std::cout << "Read as byte :";
    std::cout << static_cast<unsigned>(test.as_bytes.byte0) << std::endl; 
    
    return 0;
}