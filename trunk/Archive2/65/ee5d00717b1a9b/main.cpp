#include <iostream>
#include <iterator>
#include <algorithm>

int main()
{
    const int NROWS = 3 ;
    const int NCOLS = 4 ;
    int arr[NROWS][NCOLS] = { { 11, 12, 13, 14 }, { 21, 22, 23, 24 }, { 31, 32, 33, 34 } };

    std::rotate( std::begin( arr[0] ), std::begin( arr[0] ) + NCOLS, std::end( arr[NROWS-1] ) );

    for( const auto& row : arr )
    {
        for( int v : row ) std::cout << v << ' ' ;
        std::cout << '\n' ;
    }
}
