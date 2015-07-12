#include <iostream>
#include <locale>
#include <cwchar>
#include <codecvt>
#include <cctype>
#include <algorithm>
#include <fstream>

struct my_mbstate {}; // trivialised (use only for testing)

template < typename C, typename EXTC > struct my_code_cvt final // : std::codecvt_base
{
    using state_type = my_mbstate ;

    bool always_noconv() const noexcept  { return false ; }

    std::codecvt_base::result out( my_mbstate&,
                        const C* from, const C* from_end, const C*& from_next,
                        EXTC* to, EXTC* to_end, EXTC*& to_next ) const noexcept
    {
        // if( from && from_end && from_end > from && to && to_end && to_end > to )
        {
            const auto n = std::min( from_end - from, to_end - to ) ;
            for( std::ptrdiff_t i = 0 ; i < n ; ++i )
                to[i] = std::toupper( EXTC( std::wctob(from[i]) ) ) ; // trivialised (use only for testing)
            from_next = from + n ;
            to_next = to + n ;
            return std::codecvt_base::ok ;
        }

        return std::codecvt_base::noconv ;
    }

    std::codecvt_base::result in( my_mbstate&, const EXTC*, const EXTC*, const EXTC*&,
                                             C*, C*, C*& ) const noexcept
    { return std::codecvt_base::noconv ; }

    std::codecvt_base::result unshift( my_mbstate&, EXTC*, EXTC*, EXTC*& ) const noexcept
    { return std::codecvt_base::noconv ; }

    int encoding() const noexcept  { return 1 ; }

    int length( my_mbstate&, const EXTC* from, const EXTC* from_end, std::size_t max ) const noexcept
    { return std::min<int>( from_end - from, max ) ; }

    int max_length() const noexcept  { return 1 ; }

    static const std::locale::id id ;
};

template < typename C, typename EXTC >
const std::locale::id my_code_cvt<C,EXTC>::id = std::codecvt<char,char,std::mbstate_t>::id ;

int main()
{
    {
        std::filebuf file_buf ;
        file_buf.open( "test.txt", std::ios_base::out ) ;

        std::wbuffer_convert< my_code_cvt < wchar_t, char > > wfbuf( std::addressof(file_buf) ) ;
        std::wostream stm( std::addressof(wfbuf) ) ;

        const wchar_t cwstr[] = L"expect upper case: hello world! " ;
        stm << cwstr << std::hex << std::showbase << 12345678 << L' ' << std::boolalpha << true << L'\n' ;
        std::cout << "good? " << std::boolalpha << stm.good() << '\n' ;
    }

    { std::cout << std::ifstream( "test.txt" ).rdbuf() << '\n' ; }
}
