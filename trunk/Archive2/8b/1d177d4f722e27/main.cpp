#include <iostream>
#include <type_traits>

namespace detail
{
    template <typename T > struct bits_
    {
        static_assert( std::is_integral<T>::value, "expected an integral type" ) ;
        using uint_type = typename std::make_unsigned<T>::type; // C++14: std::make_unsigned_t<T>
        uint_type number ;
        bool first_digit = true ;
        explicit bits_( uint_type n ) : number(n) {}
    };
}

template < typename CHAR_TYPE, typename TRAITS_TYPE, typename T >
std::basic_ostream<CHAR_TYPE,TRAITS_TYPE>&
operator<< ( std::basic_ostream<CHAR_TYPE,TRAITS_TYPE>& stm, detail::bits_<T> b )
{
    if( b.number == 0 && b.first_digit ) return stm << 0 ;
    else if( b.number == 1 ) return stm << +(b.number) ;
    else
    {
        b.first_digit = false ;
        const int last_digit = b.number%2 ;
        b.number /= 2 ;
        return stm << b << last_digit ;
    }
    // TODO: add support for showbase
}

template <typename T > detail::bits_<T> bits( T n ) { return detail::bits_<T>(n) ; }

int main()
{
    for( int i : { 0, 1023, 256, 100, 0x01000010, -1 } ) std::cout << bits(i) << '\n' ;

    std::cout << bits( char(-1) ) << '\n' << bits(18LL) << '\n' << bits( -1LL ) << '\n' ;
    std::wcout << bits( char(-1) ) << L'\n' << bits(18LL) << L'\n' << bits( -1LL ) << L'\n' ;
}
