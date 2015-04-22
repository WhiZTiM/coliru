#include <iostream>

int main() {    
    int a = 32;
    volatile int b = 32;
    std::cout << "1<<32==1<<32: " << std::boolalpha << ((1<<32)<<1 == 1<<32) << std::endl;
    std::cout << "1<<31<<1==1<<31<<1: " << std::boolalpha << ((1<<31)<<1 == (1<<31)<<1) << std::endl;
    std::cout << "1<<a==1<<a: " << std::boolalpha << (1<<a == 1<<a) << std::endl;
    std::cout << "1<<b==1<<b: " << std::boolalpha << (1<<b == 1<<b) << std::endl;
}