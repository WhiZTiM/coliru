#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
    const char* const path = "data.txt" ;

    // create a test file
    {
       std::ofstream(path) << "apples bananas dates\n"
                              "bananas cherries figs\n"
                              "cherries apples eggs\n"
                              "dates eggs figs\n"
                              "eggs apples bananas\n"
                              "figs apples dates\n" ;
    }

    std::ifstream ifs(path) ;
    std::string line ;

    while( std::getline( ifs, line ) )
    {
        std::istringstream ss(line);
        std::string word ;
        while( ss >> word ) std::cout << word << ' ';
        std::cout << '\n' ;
    }
}
