#include <iostream>

int main()
{
    uint64_t raw = 0x3FA999999999999A;
    double x = reinterpret_cast<double&>(raw);

    std::cout<<x<<std::endl;

    return 0;
}
