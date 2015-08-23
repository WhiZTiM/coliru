#include <iostream>
#include <vector>
#include <string>

std::string to_string( const std::vector< std::vector< unsigned char > >& bytes )
{
    std::string result ;
    for( const auto& vec : bytes ) for( char c : vec ) result += c ;
    return result ;
}

int main()
{
    std::vector< std::vector< unsigned char > > seq { {'a','b','c'}, {'d','e','f', 'g' }, {}, {'h', 'i','j'} } ;
    std::cout << to_string(seq) << '\n' ;
}
