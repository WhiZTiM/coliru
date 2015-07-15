#include <iostream>
#include <cstdint>
#include <iomanip>
#include <limits>

bool has_digits_666( unsigned int number )
{
    while( number > 665 )
    {
        if( number%1000 == 666 ) return true ;
        number /= 10 ;
    }

    return false ;
}

int main()
{
    std::uint16_t n = 2 ; // unsigned 16-bit wide integer
    int cnt = 50 ;

    for( unsigned int i = 0 ; cnt > 0 ; ++i ) // unsigned
    {
        if( has_digits_666(i) )
        {
            if( n == 1 )
            {
                constexpr int width = std::numeric_limits<int>::digits10 + 3 ;
                std::cout << std::setw(width) << i << ' ' ;
                if( --cnt % 5 == 0 ) std::cout << '\n' ; // 5 numbers per line
            }
            --n ;
        }
    }
}
