#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>

std::string trim( std::string str )
{
    static std::istringstream stm ;
    stm.clear() ;
    stm.str(str) ;
    return stm >> str ? str : "" ;
}

void process_line( std::vector< std::vector<std::string> >& vec, const std::string& line )
{
    static std::istringstream stm ;

    stm.clear() ;
    stm.str(line) ;

    if( vec.empty() ) vec.resize(1) ;
    std::size_t col = 0 ;

    std::string token ;
    while( std::getline( stm, token, ',' ) )
    {
        if( vec.size() < ( col+1 ) )
        {
            vec.resize( col+1 ) ;

            // for all previous lines, pad up with empty strings
            vec[col].resize( vec.front().size() - 1 ) ;
        }

        vec[col++].push_back( trim(token) ) ;
    }

    // take care of this line not having all the values
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
        for( int j = 0 ; j < nvalues + (i%3) * (i%5+1) ; ++j ) file << i * 10 + j + 10 << ',' ;
        if( i%2 ) file << 88 ;
        file << '\n' ;
    }

    // to verify that empty values, and trimming are handled correctly
    file << "   ab   " << "    ,  ,,   " << 98 << "    , , cd,,,," << 99 << ",,,,," ;
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
        // use a period as placeholder for empty strings, a vertical bar as placeholder for end of line
        for( const auto& str : row ) std::cout << std::setw(4) << ( str.empty() ? "." : str ) ;
        std::cout << "|\n" ;
    }
}
