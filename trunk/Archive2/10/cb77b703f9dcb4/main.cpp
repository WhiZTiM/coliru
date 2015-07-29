#include <iostream>
#include <bitset>

enum CombineType {
    	COMBINE_FALSE = 0, COMBINE_TRUE = 1
};

int main() {
    //
    //
    //
    
    CombineType c0 = COMBINE_FALSE;
    CombineType c1 = COMBINE_TRUE;
    
    std::cout << "sizeof(c0)=" << sizeof(c0) << " c0=" << std::bitset<32>(c0)  << std::endl;
    std::cout << "sizeof(c1)=" << sizeof(c1) << " c1=" << std::bitset<32>(c1)  << std::endl;
    std::cout << std::endl;
    
    //
    //
    //
    
    bool x = true;
    unsigned int y = (unsigned int)x;
    
    std::cout << "sizeof(x)=" << sizeof(x) << " x=" << std::bitset<8>(x)  << std::endl;
    std::cout << "sizeof(y)=" << sizeof(y) << " y=" << std::bitset<32>(y)  << std::endl;
}
