#include <iostream>
#include <boost/range/irange.hpp>

auto operator "" _r( unsigned long long v ) { return boost::irange( 0, int(v), 1 ) ; }

int main()
{
    for( auto v : 16_r ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}
