#include <iostream>

int main()
{
    double x;
    const uint64_t raw = 0x3FA999999999999A;
    std::memcpy(&x, &raw, sizeof raw); 
    std::cout<<x<<std::endl;

    return 0;
}
