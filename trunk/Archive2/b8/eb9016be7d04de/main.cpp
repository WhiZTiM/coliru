#include <iostream>
#include <type_traits>

namespace detail
{
    template <typename T > struct uint_type
    {
        static_assert( std::is_integral<T>::value || std::is_enum<T>::value, "expected an integral type" ) ;
        using type = typename std::make_unsigned<T>::type;
    };

    template <typename T > struct bits_
    {
        using uint_type = typename uint_type<T>::type ;
        uint_type number ;
        bool first_use = true ;

        bits_( T n, bool first_use = false ) : number( uint_type(n) ), first_use(first_use) {}
        bits_<uint_type> next() const { return first_use ? number : number/2 ; }
    };

    struct flags_saver
    {
        std::ios_base::fmtflags flags ;
        std::ios_base& stm ;

        explicit flags_saver( std::ios_base& stm ) : flags( stm.flags() ), stm(stm) {}
        ~flags_saver() { stm.flags(flags) ; }
    };
}

template < typename CHAR_TYPE, typename TRAITS_TYPE, typename T >
std::basic_ostream<CHAR_TYPE,TRAITS_TYPE>&
operator<< ( std::basic_ostream<CHAR_TYPE,TRAITS_TYPE>& stm, detail::bits_<T> b )
{
    if( b.first_use )
    {
        detail::flags_saver saved_flags(stm) ;
        stm << std::noshowbase << std::noshowpos ;
        if( saved_flags.flags & std::ios_base::showbase )
            stm << 0 << ( saved_flags.flags & std::ios_base::uppercase ? 'B' : 'b' ) ;
        if( b.number == 0 ) return stm << 0 ;
        else return stm << b.next() ;
    }

    if( b.number == 0 ) return stm ;
    else if( b.number == 1 ) return stm << 1 ;
    else return stm << b.next() <<  b.number%2 ;
}

template <typename T > auto bits( T n )
{
    using type = typename detail::uint_type<T>::type ;
    return detail::bits_<type>( type(n), true ) ;
}

int main()
{
    for( int i : { 0, 1023, 256, 100, 0x01000010, -1 } ) std::cout << bits(i) << '\n' ;

    std::cout << std::showbase << bits( char(-1) ) << '\n' << bits( short(-1) ) << '\n' << bits(18LL)
              << '\n' << bits( -1LL ) << '\n' ;

    std::wcout << std::showbase << std::uppercase << bits( char(-1) ) << '\n' << bits( short(-1) ) << L'\n'
               << L'\n' << bits(18LL) << L'\n' << bits( -1LL ) << L'\n' ;

    enum class bitmask : short { NONE=0, A=1, B=8, C=32, ALL = -1 } ;
    std::cout << bits(bitmask::C) << '\n' << bits(bitmask::ALL) << '\n'
              << std::noshowbase << bits(bitmask::C) << '\n' << bits(bitmask::ALL) << '\n' ;

    // bits(56.7) ; // static assertion failed: expected an integral type|
}
