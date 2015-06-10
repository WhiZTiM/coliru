#include <iostream>
#include <cmath>
#include <cstring>
 
int main()
{
    // typical usage
    std::cout << "pow(2, 10) = " << std::pow(2,10) << '\n'
              << "pow(2, 0.5) = " << std::pow(2,0.5) << '\n'
              << "pow(-2, -3) = " << std::pow(-2,-3) << '\n';
    // special values
    std::cout << "pow(-1, NAN) = " << std::pow(-1,NAN) << '\n'
              << "pow(+1, NAN) = " << std::pow(+1,NAN) << '\n'
              << "pow(INFINITY, 2) = " << std::pow(INFINITY, 2) << '\n'
              << "pow(INFINITY, -1) = " << std::pow(INFINITY, -1) << '\n';
    // error handling 
    errno = 0;
    std::cout << "pow(-1, 1/3) = " << std::pow(-1, 1.0/3) << '\n';
    std::cout << "pow(-0, -3) = " << std::pow(-0.0, -3) << '\n';
}