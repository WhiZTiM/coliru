#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

enum class genre { fiction, nonfiction, periodical, biography, children };

namespace
{
    constexpr const char* genre_names[] { "fiction", "nonfiction", "periodical", "biography", "children" } ;
    constexpr std::size_t genre_count = sizeof(genre_names) / sizeof( genre_names[0] ) ;
    const std::string scope = "genre" ;
    const std::string prefix = scope + "::" ;
}

std::istream& operator>> ( std::istream& stm, genre& g ) // input
{
    std::string str ;
    if( stm >> str )
    {
        for( char& c : str ) c = std::tolower(c) ; // ignore case
        const auto prefix_begin = str.find(prefix) ;
        if( prefix_begin == 0 ) str = str.substr( prefix.size() ) ; // scope prefix is optional

        for( std::size_t pos = 0 ; pos < genre_count ; ++pos ) if( str == genre_names[pos] )
        {
            g = genre(pos) ;
            return stm ;
        }
    }

    // attempted input failed
    stm.setstate( stm.rdstate() | std::ios_base::failbit ) ;
    return stm ;
}

std::ostream& operator<< ( std::ostream& stm, genre g ) // output
{
    const unsigned int ival = unsigned(g) ;
    assert( ival < genre_count ) ;

    if( ival < genre_count ) return stm << prefix << genre_names[ival] ;
    else return stm << "genre::invalid_value(" << ival << ')' ; // may want to throw
}

int main()
{
    genre g{} ;

    while( std::cin >> g ) std::cout << g << "   " ;
    
    g = genre(56) ;
    std::cout << g << '\n' ;
}
