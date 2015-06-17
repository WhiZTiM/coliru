#include <iostream>
#include <string>
 
std::string trim( std::string const& str ) {
    static const char * whitespaces{" \n\t\r\v\f"};
    std::size_t first = str.find_first_not_of(whitespaces);
    if (first == std::string::npos) return "";
    return str.substr(first,str.find_last_not_of(whitespaces)-first+1);
}

int main()
{
    std::string str{"   Hello World!  "};
    
    std::cout << "[" << trim( str ) << "]\n";
}