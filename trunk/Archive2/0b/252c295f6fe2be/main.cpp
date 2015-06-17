#include <iostream>
#include <string>
 
std::string trim( const std::string & str ) {
    static constexpr space std::string{" \n\t\r\v\f"};
    auto first = str.find_first_not_of(space);
    auto last = str.find_last_not_of(space);
    if (first == std::string::npos) return "";
    return str.substr(first,last-first+1);
}

int main()
{
    std::string str{"   Hello World!  "};
    
    std::cout << "\"" << trim( str ) << "\"\n";
}