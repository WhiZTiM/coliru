#include <iostream> // "std_lib_facilities.h"
#include <vector>
#include <algorithm>

#include <functional>
#include <cassert>

int main()
{
    const std::vector<int> ivec { 0, 2, 6, 4, 8, 9, 3, 7, 5, 1 };

    for( int value : { 9, -7 } )
    {
        std::cout << "find " << value << " in range: " ;
        using std::placeholders::_1 ;

        const auto p1 = std::find_if( ivec.begin(), ivec.end(), std::bind( std::equal_to<int>{}, _1, value ) );
        const auto p2 = std::find_if( ivec.begin(), ivec.end(), std::bind( std::equal_to<int>(), _1, value ) );

        const auto p3 = std::find_if( ivec.begin(), ivec.end(), std::bind( std::equal_to<>{}, _1, value ) ); // C++14
        const auto p4 = std::find_if( ivec.begin(), ivec.end(), std::bind( std::equal_to<>(), _1, value ) ) ; // C++14

        const auto p5 = std::find_if( ivec.begin(), ivec.end(), [value]( int v ) { return v == value ; } ); // simple
        const auto p6 = std::find( ivec.begin(), ivec.end(), value ); // simplest

        assert( (p1==p2) && (p2==p3) && (p3==p4) && (p4==p5) && (p5==p6) ) ;

        if( p1 != ivec.end() ) std::cout << "found " << *p1 << '\n' ;
        else std::cout << "not found\n";
    }
}
