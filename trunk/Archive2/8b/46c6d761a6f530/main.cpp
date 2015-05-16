#include <iostream>
#include <string>

bool find( std::string bigger_str, std::size_t start_pos, std::string smaller_str )
{
    if( bigger_str.size() < ( smaller_str.size() + start_pos ) ) return false ;

    for( std::size_t i = 0 ; i < smaller_str.size() ; ++i )
        if( smaller_str[i] != bigger_str[i+start_pos] ) return false ;

    return true ;
}

int main()
{
    const std::string bigger = "abracrabradrabra" ;
    std::cout << bigger << "\n01234567890123456789\n\n" ;

    const std::string smaller = "abr" ;

    for( std::size_t pos = 0 ; pos < bigger.size() ; ++pos )
        if( find( bigger, pos, smaller ) )
           std::cout << "found '" << smaller << "' at position " << pos << '\n' ;
}
