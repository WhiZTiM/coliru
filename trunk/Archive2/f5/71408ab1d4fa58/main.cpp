#include <iostream>
#include <iterator>
#include <string>

template < typename SEQUENCE > void print( const SEQUENCE& seq ) {

    // using iterator = decltype( std::begin(seq) ) ; // type alias for the type of iterator
    // auto is simpler
    for( auto iter = std::begin(seq) ; iter != std::end(seq) ; ++iter ) {
        std::cout << *iter << ' ' ;
    }
    std::cout << '\n' ;
}

template < typename SEQUENCE > void easy_print( const SEQUENCE& seq ) {

    for( const auto& value : seq ) std::cout << value << ' ' ;
    std::cout << '\n' ;
}

int main()
{
    const std::string str = "abcd" ;
    print(str) ;
    easy_print(str) ;

    const int a[] { 56, 78, 90, 12, 34 } ;
    print(a) ;
    easy_print(a) ;
}
