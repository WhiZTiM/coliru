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
        static std::vector<mask> table( classic_table(),  classic_table() + table_size ) ;
        table[ ',' ] |= space ; // comma is whitespace
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
    static auto loc = comma_is_ws::apply(stm) ;

    std::size_t col = 0 ;
    stm.clear() ;
    stm.str(line) ;
    std::string token ;
    while( stm >> token )
    {
        if( vec.size() < (col+1) ) vec.resize( col+1 ) ;
        //for( auto s : vec[col] ) std::cout << s << ' ' ; std::cout << " *\n" ;

        vec[col].push_back(token) ;
        ++col ;
    }
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
    std::ofstream file(path) ;
    for( int i = 0 ; i < nlines ; ++i )
    {
        for( int j = 0 ; j < nvalues ; ++j ) file << i*10 + j + 10 << ',' ;
        file << '\n' ;
    }
}

int main()
{
    const char* const path = "/Archive2/85/294b94a82ae3c6/test.txt" ;
    transpose_read_csv( std::ifstream(path)  ) ; //  )
}
