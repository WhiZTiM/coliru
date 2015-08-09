#include <iostream>
#include <fstream>

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
    const char* const path = "test.txt" ;
    const int nlines = 5000 ;
    const int nvalues_per_line = 100 ;
    create_test_file( path, nlines, nvalues_per_line ) ;
}
