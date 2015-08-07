#include <iostream>
#include <string>

bool has_suffix( std::string str, std::string suffix )
{
    return str.size() > suffix.size() &&
           str.rfind( suffix ) == ( str.size() - suffix.size() ) ;
}

std::string expand_not( std::string str )
{
    // special cases:
    if( has_suffix( str, "'t" ) )
    {
        if( str == "won't" ) return "will not" ;
        else if( str == "shan't" ) return "shall not" ;
        // else if ...

        // else the general case
        if( has_suffix( str, "n't" ) ) return str.substr( 0, str.size() - 3 ) + ' ' + "not" ;
    }

    return str ;
}

int main()
{
    for( std::string str : { "wouldn't", "won't", "shan't", "didn't", "hello", "don't" } )
         std::cout << str << "  =>  " << expand_not(str) << '\n' ;
}