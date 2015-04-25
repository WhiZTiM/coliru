#include <iostream>
#include <limits>

int nearest_odd_integer( double v )
{
    if( v >= std::numeric_limits<int>::max() ) return std::numeric_limits<int>::max() ;
    else if( v <= std::numeric_limits<int>::min() ) return std::numeric_limits<int>::min() + 1 ;

    bool negative = false ;
    if( v < 0 ) { negative = true ; v = -v ; }

    int ival = v ; // truncation towards zero
    if( ival%2 == 0 ) ++ival ; // even, nearest odd integer is i+1

    return negative ? -ival : ival ;
}

int main()
{
    for( double d : { -1.0e+30, -2.9, -2.3, -2.0, -1.99, -0.6, -0.01, 0.0, +0.01, +0.7, +1.8, +2.0, +2.3, 1.0e+30,  } )
        std::cout << d << " => " << nearest_odd_integer(d) << '\n' ;
}
