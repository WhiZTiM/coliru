#include <iostream>
#include <string>
#include <regex>

bool is_valid_phone_number( std::string str )
{
    // http://www.stroustrup.com/C++11FAQ.html#raw-strings
    static const std::regex pattern( R"(\d\d\d\-\d\d\d\-\d\d\d\d)" ) ; // \d - decimal digit [0-9]
    return std::regex_match( str, pattern ) ;
}

int main()
{
    for( std::string str : { "123-123-1234", "123-1234-123", "123-123-123", "123-1a3-1234", "003-023-0004", "123-123_1234 " } )
        std::cout << '"' << str << '"' << ( is_valid_phone_number(str) ? " ok\n" : " invalid\n" ) ;
}
