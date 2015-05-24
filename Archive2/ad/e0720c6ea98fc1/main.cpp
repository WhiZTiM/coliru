#include <iostream>
#include <iomanip>
#include <cfenv>
#include <cmath>

int main()
{
    std::cout << std::fixed << std::setprecision(2) ;
    
    #pragma STDC FENV_ACCESS ON // standard C99 pragma, ignored by clang++, g++, and msvc++

    std::fesetround( FE_TOWARDZERO ) ; // the first call to fesetround() appears to be supported by all three compilers
    std::cout << "FE_TOWARDZERO: " << 99.0 / 5.0 << ", " << 99.0 / -5.0 << " => " 
              << std::nearbyint( 99.0 / 5.0 ) << ", " << std::nearbyint( 99.0 / -5.0 ) << '\n' ;

    std::fesetround( FE_TONEAREST ) ; // but only the microsoft compiler appears to support subsequent calls
    std::cout << " FE_TONEAREST: "  << 99.0 / 5.0 << ", " << 99.0 / -5.0 << " => " 
              << std::nearbyint( 99.0 / 5.0 ) << ", " << std::nearbyint( 99.0 / -5.0 ) << '\n' ;

    std::fesetround( FE_DOWNWARD ) ; // but only the microsoft compiler appears to support subsequent calls
    std::cout << "  FE_DOWNWARD: " << 99.0 / 5.0 << ", " << 99.0 / -5.0 << " => " 
              << std::nearbyint( 99.0 / 5.0 ) << ", " << std::nearbyint( 99.0 / -5.0 ) << '\n' ;
}
