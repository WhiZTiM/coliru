#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// https://en.wikipedia.org/wiki/Euclidean_algorithm
// https://en.wikipedia.org/wiki/Euclidean_algorithm#Implementations
unsigned int gcd_e( unsigned int a, unsigned int b ) { return b == 0 ? a : gcd_e( b, a%b ) ; }

unsigned int gcd_fp( unsigned int a, unsigned int b ) // find common divisors in parallel
{
    unsigned int gcd = 1 ;

    for( unsigned int i = 2 ; i<a && i<b ; ++i )
    {
        while( a%i==0 && b%i == 0 ) // if i is a common divisor
        {
           gcd *= i ;
           a /= i ;
           b /= i ;
        }
    }

    return gcd ;
}

// https://cal-linux.com/tutorials//vectors.html
std::vector<unsigned int> non_unique_prime_divisors_of( unsigned int n )
{
    std::vector<unsigned int> result ;

    for( unsigned int i = 2 ; i < n ; ++i )
    {
        while( n%i == 0 )
        {
           result.push_back(i) ;
           n /= i ;
        }
    }

    if( n != 1 ) result.push_back(n) ;
    return result ;
}

unsigned int gcd_f( unsigned int a, unsigned int b ) // find common divisors one by one
{
    const auto fa = non_unique_prime_divisors_of(a) ;
    const auto fb = non_unique_prime_divisors_of(b) ;

    // common non-unique prime divisors of a and b
    // http://en.cppreference.com/w/cpp/algorithm/set_intersection
    std::vector<unsigned int> common_divisors ;
    std::set_intersection( std::begin(fa), std::end(fa),
                           std::begin(fb), std::end(fb),
                           std::back_inserter(common_divisors) ) ;

    unsigned int gcd = 1 ;
    for( auto divisor : common_divisors ) gcd *= divisor ;
    return gcd ;
}

int main()
{
    std::cout << gcd_e( 315, 2310 ) << '\n'
              << gcd_fp( 315, 2310 ) << '\n'
              << gcd_f( 315, 2310 ) << '\n' ;
}
