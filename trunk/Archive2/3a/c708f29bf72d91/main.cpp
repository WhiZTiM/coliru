// https://codereview.stackexchange.com/questions/40124/trim-white-space-from-string

#include <iostream>
#include <string>
 
std::string trim(std::string const& str)
{
    if(str.empty())
        return str;
    std::size_t firstScan = str.find_first_not_of(' ');
    std::size_t first     = firstScan == std::string::npos ? str.length() : firstScan;
    std::size_t last      = str.find_last_not_of(' ');
    return str.substr(first, last-first+1);
}

int main()
{
    std::cout << "["
        << trim( "" )          // null string
        << trim( " " )         // single space
        << trim( "  Hello" )   // leading only
        << trim( "  " )        // only spaces, more than one
        << trim( ", W  " )     // internal and trailing
        << trim( " orld  " )   // leading and trailing
        << trim( "!  " )       // trailing only
        << "]\n";
        
    // expected output: [Hello, World!]
}
