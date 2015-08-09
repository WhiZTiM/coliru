#include <iostream>
#include <locale>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>

// a ctype facet that trats comma as whitespace. 
// note: this facet is required if the values in the csv file need to be trimmed efficiently
// if trimming is not required,  while( stm >> token ) in process_line() 
// can be replace by while( std::getline( stm, line, ',' ) )
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
    { return stm.imbue( std::locale( stm.getloc(), new comma_is_ws ) ) ; }
};

void process_line( std::vector< std::vector<std::string> >& vec, const std::string& line )
{
    static std::istringstream stm ;
    static auto loc = comma_is_ws::apply( stm ) ; // comment out if tokens need not be trimmed 

    stm.clear() ;
    stm.str( line ) ;

    if( vec.empty() ) vec.resize( 1 ) ;
    std::size_t col = 0 ;

    std::string token ;
    while( stm >> token ) // replace with while( std::getline( stm, line, ',' ) ) if tokens need not be trimmed
    {
        if( vec.size() < ( col + 1 ) )
        {
            vec.resize( col + 1 ) ; // add a new row
            vec[col].resize( vec.front().size() - 1 ) ; // and resize it with empty strings for earlier lines
        }

        vec[col].push_back( token ) ;
        ++col ;
    }

    while( col < vec.size() ) vec[col++].emplace_back( "" ) ; // take care of not enough values
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
        for( int j = 0 ; j < nvalues + (i%3) * (i%5+1) ; ++j ) file << i * 10 + j + 10 << ',' ;
        file << '\n' ;
    }
    file << 97 << "    ,    " << 98 << "    ,    " << 99 << '\n' ; // to verify that strings will be trimmeds
}

int main()
{
    const char* const path = "test.txt" ;
    const int nlines = 5 ;
    const int nvalues_per_line = 10 ;
    create_test_file( path, nlines, nvalues_per_line ) ;

    std::cout << std::ifstream( path ).rdbuf() << "\n-------------\n\n" ;

    for( const auto& row : transpose_read_csv( std::ifstream( path ) ) )
    {
        for( const auto& str : row ) std::cout << std::setw(4) << ( str.empty() ? "." : str ) ; // dot as placeholder for empty strings 
        std::cout << "|\n" ; // '|' at end of line to erify that strings were trimmed
    }
}
