#include <iostream>
#include <string>
#include <fstream>

int main()
{
    //////////////////////////////////////////////////////////////
    // create the test file (this is just for testing)
    {
        std::ofstream( "marks.txt" ) <<
                                "8\n"
                                "26 21 41 john adam\n"
                                "28 24 40 sara henry\n"
                                "18 15 38 micheal adler\n"
                                "23 22 35 tyler harry\n"
                                "27 23 43 jerry lendley\n"
                                "12 19 17 emily slash\n"
                                "15 21 33 mike freddie\n"
                                "19 20 42 kylie m\n" ;
    }
    //////////////////////////////////////////////////////////////

    const int classMax = 20 ;
    const int N = 3 ;

    std::ifstream file( "marks.txt" ) ; // open the file for input
    int n_lines ;
    file >> n_lines ; // read the number of lines'

    if( n_lines > 0 && n_lines <= classMax )
    {
        int marks[classMax][N] = { {0} } ;
        std::string names[classMax] ;

        // read marks, name from eaxh line
        for( int i = 0 ; i < n_lines ; ++i )
        {
            // read the marks
            for( int j = 0 ; j < N ; ++j ) file >> marks[i][j] ;

            // read the rest of the line (ignoring leading whitespaces) as the name
            // skip leading whitespace: http://www.cplusplus.com/reference/istream/ws/
            // http://www.cplusplus.com/reference/string/string/getline/
            std::getline( file >> std::ws, names[i] ) ;
        }

        // verify that we have read everything correctly.
        for( int i = 0 ; i < n_lines ; ++i )
        {
            std::cout << i+1 << ". " << "name: '" << names[i] << "'  marks: " ;
            for( int j = 0 ; j < N ; ++j )std::cout << marks[i][j] << ' ' ;
            std::cout << '\n' ;
        }

        // TODO: process the data. find average etc.
    }
}
