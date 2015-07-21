#include <iostream>
#include <type_traits>
#include <limits>

template < typename CHAR > void test_it()
{
    CHAR c = 0 ;
    decltype(+c) i = std::numeric_limits<CHAR>::max() + 1 ;
    std::cout << +CHAR(i) << " == " << i << " ? "
              << std::boolalpha << ( CHAR(i) == i ) << '\n' ;

    i = std::numeric_limits<CHAR>::min() - 1 ;
    std::cout << +CHAR(i) << " == " << i << " ? "
              << std::boolalpha << ( CHAR(i) == i ) << '\n' ;
}

int main()
{
    std::cout << "\nchar\n------------\n" ; test_it<char>() ;
    std::cout << "\nsigned char\n------------\n" ; test_it< signed char >() ;
    std::cout << "\nunsigned char\n------------\n" ; test_it< unsigned char >() ;
}
