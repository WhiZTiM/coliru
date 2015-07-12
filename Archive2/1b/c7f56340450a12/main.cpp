#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

int main()
{
    boost::multiprecision::int512_t a = 0x80000;
    int shift = 512 - 20;
    a = (a << shift) >> shift;
    
    boost::multiprecision::int512_t b;
    b = (0x80000 << shift) >> shift;
    
    std::cout <<  a  << " " << b << std::endl;
    return 0;
}
