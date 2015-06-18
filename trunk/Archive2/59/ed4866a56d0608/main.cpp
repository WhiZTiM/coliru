#include <iostream>
#include <cmath>
#include <cerrno>
#include <cstring>
#include <cfenv>
#pragma STDC FENV_ACCESS ON
int main()
{
    std::cout << "log(1) = " << std::log(1) << '\n'
              << "base-5 logarithm of 125 = " << std::log(125)/std::log(5) << '\n';
    // special values
    std::cout << "log(1) = " << std::log(1) << '\n'
              << "log(+Inf) = " << std::log(INFINITY) << '\n';
    // error handling 
    errno=0; std::feclearexcept(FE_ALL_EXCEPT);
    std::cout << "log(0) = " << std::log(0) << '\n';
    if(errno == ERANGE)
        std::cout << "    errno == ERANGE: " << std::strerror(errno) << '\n';
    if(std::fetestexcept(FE_DIVBYZERO))
        std::cout << "    FE_DIVBYZERO raised\n";
}