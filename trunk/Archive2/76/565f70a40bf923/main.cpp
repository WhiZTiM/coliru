#include <iostream>
#include <fstream>

void create_test_file( const char* path, int nlines, int nvalues )
{
    std::ofstream file( path ) ;
    for( int i = 0 ; i < nlines ; ++i )
    {
        for( int j = 0 ; j < nvalues + (i%3) * (i%5+1) ; ++j ) file << i * 10 + j + 10 << ',' ;
        if( i%2 ) file << 88 ;
        file << '\n' ;
    }

    // to verify that empty values, and trimming of strings are handled correctly
    file << "   ab   " << "    ,  ,,   " << 98 << "    , , cd,,,," << 99 << ",,,,," ;
}

int main()
{
    const char* const path = "test.txt" ;
    const int nlines = 6667 ;
    const int nvalues_per_line = 100 ;
    create_test_file( path, nlines, nvalues_per_line ) ;
}
