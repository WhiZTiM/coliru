#include<iostream>
#include<string>

int main()
{
    std::string str ;

    std::cout << "enter the txt: " ;
    std::getline( std::cin, str ) ;
    std::cout << "entered string is '" << str << "'\n" ;

    for( char& c : str ) if( c == ' ' ) c  = '_' ;
    // or: for( char& c : str ) if( std::isspace(c) ) c  = '_' ; // <cctype>

    std::cout << "new string is: '" << str << "'\n" ;
}
