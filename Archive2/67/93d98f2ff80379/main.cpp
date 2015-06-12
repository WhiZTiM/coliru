#include <iostream>
#include <string>
#include <functional>

const std::string one( "one" );
const std::string two = "two" ;
const std::string three { "three" };
const std::string four = { "four" };

template < typename T > void print( const T& v ) { std::cout << v << ' ' ; }

template < typename FIRST, typename... REST > void print( const FIRST& first, const REST&... rest )
{
    print(first) ;
    print(rest...) ;
}

int main()
{
    // copy-elision is possible
    for( const auto& str : { one, two, three, four } ) std::cout << str << ' ' ;
    std::cout << '\n' ;

    // explicitly avoid making copies of the strings (wrap the references)
    for( const std::string& str : { std::cref(one), std::cref(two), std::cref(three), std::cref(four) } )
        std::cout << str << ' ' ;
    std::cout << '\n' ;

    // loop at compile time (variadic template)
    print( one, two, three, four, 12345, 67.89 ) ;
    std::cout << '\n' ;
}
