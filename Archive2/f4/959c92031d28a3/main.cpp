#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <iterator>

int main()
{
    const std::regex re( R"(\b(\d)\1*\b)" ) ;  // \1 is the backreference to (\d)

    const std::string str = "2222 aaa 123 bbb 5 55555555 66 cc 777 7773 37777 737777 333333333" ;

    std::copy( std::sregex_token_iterator( str.begin(), str.end(), re ), std::sregex_token_iterator(),
               std::ostream_iterator<std::string>( std::cout, "\n" ) ) ;
}
