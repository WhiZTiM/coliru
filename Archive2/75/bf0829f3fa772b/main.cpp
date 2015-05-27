#include <iostream>
#include <cmath>
#include <cfenv>
#include <climits>
 
#pragma STDC FENV_ACCESS ON
 
int main()
{
    // round
    std::cout << "round(+2.3) = " << std::round(2.3)
              << "  round(+2.5) = " << std::round(2.5)
              << "  round(+2.7) = " << std::round(2.7) << '\n'
              << "round(-2.3) = " << std::round(-2.3)
              << "  round(-2.5) = " << std::round(-2.5)
              << "  round(-2.7) = " << std::round(-2.7) << '\n';
 
    std::cout << "round(-0.0) = " << std::round(-0.0)  << '\n'
              << "round(-Inf) = " << std::round(-INFINITY) << '\n';
 
    // lround
    std::cout << "lround(+2.3) = " << std::lround(2.3)
              << "  lround(+2.5) = " << std::lround(2.5)
              << "  lround(+2.7) = " << std::lround(2.7) << '\n'
              << "lround(-2.3) = " << std::lround(-2.3)
              << "  lround(-2.5) = " << std::lround(-2.5)
              << "  lround(-2.7) = " << std::lround(-2.7) << '\n';
 
    std::cout << "lround(-0.0) = " << std::lround(-0.0)  << '\n'
              << "lround(-Inf) = " << std::lround(-INFINITY) << '\n';
 
    // error handling
    std::feclearexcept(FE_ALL_EXCEPT);
    std::cout << "std::lround(LONG_MAX+1.5) = "
              << std::lround(LONG_MAX+1.5) << '\n';
    if(std::fetestexcept(FE_INVALID))
              std::cout << "    FE_INVALID was raised\n";
}