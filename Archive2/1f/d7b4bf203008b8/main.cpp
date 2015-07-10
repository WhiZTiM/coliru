#include <iostream>
#include <iomanip>

int main()
{
    union
    {
        unsigned int ival ;
        unsigned char bytes[ sizeof(unsigned int) ] ;
    };

    ival = 0x1234abcd ;
    std::cout << "unsigned int: " << std::hex << ival << "  bytes: " ;
    for( unsigned char b : bytes )
        std::cout << std::setfill('0') << std::setw(2) << int(b) << ' ' ;
    std::cout << '\n' ;
}
