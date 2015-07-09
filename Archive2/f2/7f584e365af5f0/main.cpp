#include <iostream>
#include <string>

int main()
{
    std::string str ;

    // std::cout << "enter a string: " ;
    std::getline( std::cin, str ) ;
    std::cout << "entered string is: '" << str << "'\n" ;

    // http://www.stroustrup.com/C++11FAQ.html#for
    for( char& c : str ) if( c == ' ' ) c  = '_' ;
    
    // or: for( char& c : str ) if( std::isspace(c) ) c  = '_' ; // <cctype>

    std::cout << "    new string is: '" << str << "'\n" ;
}
