#include <iostream>
#include <bitset>
#include <type_traits>
#include <limits>
#include <string>

constexpr std::size_t ULONGLONG_BITS = std::numeric_limits<unsigned long long>::digits ;

template< std::size_t N1, std::size_t N2 >
typename std::enable_if< (N1+N2) <= ULONGLONG_BITS, std::bitset<N1+N2> >::type // efficient for small sizes
cat( const std::bitset<N1>& a, const std::bitset<N2>& b ) { return ( a.to_ullong() << N2 ) + b.to_ullong() ; }

template< std::size_t N1, std::size_t N2 > 
typename std::enable_if< ( (N1+N2) >ULONGLONG_BITS ), std::bitset<N1+N2> >::type 
cat( const std::bitset<N1>& a, const std::bitset<N2>& b ) { return std::bitset<N1+N2>( a.to_string() + b.to_string() ) ; }

int main()
{
    const std::bitset<12> a( "101100111000" ) ;
    const std::bitset<20> b( "11110000111100001111" ) ;
    const std::bitset<50> c( "11111000001111100000111110000011111000001111100000" ) ;
    std::cout << a << " cat " << b << " == " << cat(a,b) << '\n' 
              << b << " cat " << c << " == " << cat(b,c) << '\n' ;
}
