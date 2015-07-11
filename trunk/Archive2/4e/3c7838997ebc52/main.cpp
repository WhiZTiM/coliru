#include <iostream>
#include <locale>
#include <cwchar>
#include <cctype>
#include <typeinfo>
#include <algorithm>
#include <fstream>

struct my_code_cvt : std::codecvt< char, char, std::mbstate_t >
{
    protected:
        virtual bool do_always_noconv() const noexcept override { return false ; }

        virtual std::codecvt_base::result do_out( std::mbstate_t& state,
            const char* from, const char* from_end, const char*& from_next,
            char* to, char* to_end, char*& to_next ) const override
        {
            if( std::mbsinit( std::addressof(state) ) &&
                from && from_end && from_end > from &&
                to && to_end && to_end > to )
            {
                const auto n = std::min( from_end - from, to_end - to ) ;
                for( std::ptrdiff_t i = 0 ; i < n ; ++i ) to[i] = std::toupper( from[i] ) ;
                from_next = from + n ;
                to_next = to + n ;
                return std::codecvt_base::ok ;
            }

            return std::codecvt_base::noconv ;
        }
};

void test( std::ostream& stm, const char* header )
{
    stm << '\n' << header << "\n--------------\n" << "\nmy_code_cvt facet installed? " << std::boolalpha ;
    try
    {
        const auto& facet = std::use_facet<my_code_cvt>( stm.getloc() ) ;
        stm << ( typeid(facet) == typeid(my_code_cvt) ) << '\n' ;
    }
    catch( const std::exception& ) { stm << "false\n" ; }
    stm << "hello " << "world! " << std::hex << std::showbase << 12345678 << '\n' << std::flush ;

    stm.imbue( std::locale( stm.getloc(), new my_code_cvt ) ) ;
    stm << "\nmy_code_cvt facet installed? " << std::boolalpha ;
    try
    {
        const auto& facet = std::use_facet<my_code_cvt>( stm.getloc() ) ;
        stm << ( typeid(facet) == typeid(my_code_cvt) ) << '\n' ;
    }
    catch( const std::exception& ) { stm << "false\n" ; }
    stm << "hello " << "world! " << std::hex << std::showbase << 12345678 << "\n\n" << std::flush ;
}

int main()
{
    std::ios_base::sync_with_stdio(false) ; // **** required by libstdc++
    
    test( std::cout, "test standard stream"  ) ;

    {
        std::ofstream file( "test.txt" ) ;
        test( file, "test file stream" ) ;
    }
    { std::clog << std::ifstream( "test.txt" ).rdbuf() ; }
}
