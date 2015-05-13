#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::cout.setf(std::ios::showpoint);
    std::cout << std::pow((long double)9, (long double)19) << std::endl;
    
    return 0;
}