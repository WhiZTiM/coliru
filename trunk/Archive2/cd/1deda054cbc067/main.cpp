#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
    const char* const path = "data.txt" ;

    {
        std::ofstream(path) <<  "apples bananas dates\n"
                                "bananas cherries figs\n"
                                "cherries apples eggs\n"
                                "dates eggs figs\n"
                                "eggs apples bananas\n"
                                "figs apples dates\n" ;
    }

    std::ifstream file(path);
    const std::string search_str = "apples"; // *** apples ***

    std::string line ;
    while( getline( file, line ) )
    {
        std::istringstream stm(line) ;
        std::string word ;
        while( stm >> word )
        {
            if( word == search_str )
            {
                std::cout << stm.str() << '\n' ;
                break ;
            }
        }
    }
}
