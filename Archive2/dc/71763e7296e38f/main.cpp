#include <iostream>
#include <string>
#include <map>

std::map< std::string, int > read_map( std::istream& stm = std::cin )
{
    std::map< std::string, int > map ;
    std::string key ;
    int value ;

    // key does not contain white space
    while( stm >> key >> value ) map.emplace( key, value ) ;

    /*
    // key may contain white space
    while( std::getline( stm, key ) && // read a complete line as key (unformatted input)
           stm >> value && // read an int as value (formatted input)
           stm.ignore( 1000000, '\n' ) ) // extract and discard the trailing new line
               map.emplace( key, value ) ;
    */

    return map ;
}

int main()
{
    for( const auto& p : read_map() ) std::cout << p.first << ' ' << p.second << '\n' ;
}
