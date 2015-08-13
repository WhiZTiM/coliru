#include <iostream>
#include <string>

template < typename FIRST, typename SECOND >
constexpr bool equal_to( const FIRST& first, const SECOND& second )
{ return first == second ; }


template < typename FIRST, typename SECOND, typename... REST >
constexpr bool equal_to( const FIRST& first, const SECOND& second, const REST&... rest )
{ return equal_to( first, second ) && equal_to( second, rest... )  ; }

int main()
{
    const short s = 1 ;
    const std::string s1 = "abcd", s2 = s1 ;
    const char cstr[] = "abcd" ;
    const char* ptr = cstr ;

    std::cout << std::boolalpha << equal_to( 1, s ) << '\n' // true
              << equal_to( 1, 1LL, 1L, 2-1, 1, 1, s ) << '\n' // true
              << equal_to( 1, 1LL, 1L, 1, 1, 1, s, +s, 'A', 3.42 ) << '\n' // false
              << equal_to( s1, "abcd", s2, cstr, ptr ) << '\n' ; // true
}
