#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

bool cat( std::string file_one, std::string file_two )
{ return bool( std::ofstream( file_one, std::ios_base::app ) << std::ifstream(file_two).rdbuf() ) ; }

int main()
{
    const std::string my_file_name = "myfile.txt" ;

    { std::ofstream(my_file_name) << "///////////////////////\n// concatenate files //\n///////////////////////\n\n" ; }

    if( cat( my_file_name, __FILE__ )  )
    {
        std::ifstream myfile(my_file_name) ;
        int line_number = 0 ;
        std::string line ;
        while( std::getline( myfile, line ) ) std::cout << std::setw(2) << ++line_number << ". " << line << '\n' ;
    }
}
