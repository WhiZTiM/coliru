#include <iostream>
#include <cmath>
#include <iomanip>
#include <bitset>

double phi(double x1, double x2)
{
    return (std::erf(x2/std::sqrt(2)) - std::erf(x1/std::sqrt(2)))/2;
}
int main()
{
    double a = -2.36211856075265944077e-03;
    
    std::cout << std::hexfloat;
    std::cout << a << std::endl;
    std::cout << std::hex;
    std::cout << *reinterpret_cast<size_t*>(&a) << std::endl;
    std::cout << std::bitset<64>(a) << std::endl;
    std::cout << std::bitset<64>(*reinterpret_cast<size_t*>(&a)) << std::endl;  
}