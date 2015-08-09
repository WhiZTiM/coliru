#include <iostream>
#include <locale>
#include <vector>
#include <sstream>
#include <fstream>

struct comma_is_ws : std::ctype<char>
{
    static const mask* table()
    {
        // start with the classic table
        static std::vector<mask> table( classic_table(), classic_table() + table_size ) ;
        table[','] |= space ; // comma is whitespace
        return std::addressof( table.front() ) ;
    }

    // do not delete table, initial reference count == 0
    comma_is_ws() : std::ctype<char>( table() ) {}

    static std::locale apply( std::istream& stm )
    {
        return stm.imbue( std::locale( stm.getloc(), new comma_is_ws ) ) ;
    }
};

void process_line( std::vector< std::vector<std::string> >& vec, const std::string& line )
{
    static std::istringstream stm ;
    static auto loc = comma_is_ws::apply( stm ) ;

    stm.clear() ;
    stm.str( line ) ;

    if( vec.empty() ) vec.resize(1) ;
    std::size_t col = 0 ;

    std::string token ;
    while( stm >> token )
    {
        if( vec.size() < ( col+1 ) )
        {
            vec.resize( col+1 ) ;
            vec[col].resize( vec.front().size() - 1 ) ;
        }

        vec[col].push_back( token ) ;
        ++col ;
    }

    while( col < vec.size() ) vec[col++].emplace_back( "" ) ;
}

std::vector< std::vector<std::string> > transpose_read_csv( std::ifstream file )
{
    std::vector< std::vector<std::string> > result ;

    std::string line ;
    while( std::getline( file, line ) ) process_line( result, line ) ;

    return result ;
}

void create_test_file( const char* path, int nlines, int nvalues )
{
    std::ofstream file( path ) ;
    for( int i = 0 ; i < nlines ; ++i )
    {
        for( int j = 0 ; j < nvalues + ( i % 3 ) * ( i % 5 + 1 ) ; ++j ) file << i * 10 + j + 10 << ',' ;
        file << '\n' ;
    }
    file << 97 << ',' << 98 << ',' << 99 << '\n' ;
}

int main()
{
    const char* const path = "test.txt" ;
    transpose_read_csv( std::ifstream( path ) );
}
