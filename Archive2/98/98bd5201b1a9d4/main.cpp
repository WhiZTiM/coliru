#include <iostream>
#include <cfenv>
#include <cmath>

int main()
{
    #pragma STDC FENV_ACCESS ON

    std::fesetround( FE_TOWARDZERO ) ;
    std::cout << std::fixed << std::nearbyint( 8.0 / 3.0 ) << '\n'
              << std::nearbyint( 8.0 / -3.0 ) << '\n' ;
}
