#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>

int main()
{
    std::vector<int> srce { 1, 2, 102, 3, 109, 3, 102, 55, 5 } ;

    std::vector<int> data( srce.size() ) ;
    // http://en.cppreference.com/w/cpp/algorithm/iota
    std::iota( std::begin(data), std::end(data), 200 ) ;

    // http://en.cppreference.com/w/cpp/algorithm/transform
    std::transform( std::begin(srce), std::end(srce), std::begin(data), std::begin(srce),
                    []( int sval, int dval ) { return sval > 100 ? dval : sval ; } ) ;

    for( int value : srce ) std::cout << value << ' ' ;
    std::cout << '\n' ;
}
