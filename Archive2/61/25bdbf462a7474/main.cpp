#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <iterator>

int main()
{
    // http://www.regular-expressions.info/wordboundaries.html
    const std::regex re( R"(\b\w{4}\b)" ) ;

    const std::string str = "want to find every four letter word. And this must be the pattern for that." ;

    // http://en.cppreference.com/w/cpp/regex/regex_token_iterator
    std::copy( std::sregex_token_iterator( str.begin(), str.end(), re ), std::sregex_token_iterator(),
               std::ostream_iterator<std::string>( std::cout, "\n" ) ) ;
}
