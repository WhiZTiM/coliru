#include <iostream>

int main()
{
    std::cout << "hex: " << std::hexfloat << 12.345 
              << "  default: " << std::defaultfloat << 12.345 << '\n' ;
}