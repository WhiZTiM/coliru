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

int main()
{
    const char* const path = "test.txt" ;
    const auto transpose_result = transpose_read_csv( std::ifstream( path ) ) ;
    std::cout << transpose_result.size() << " rows " << transpose_result[0].size() << " cols\n" ;
}
