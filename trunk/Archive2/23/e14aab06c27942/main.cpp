// http://codereview.stackexchange.com/questions/40124/trim-white-space-from-string/40302#comment170899_40302
#include <iostream>
#include <string>
 
std::string trim(std::string const& str)
{
    if(str.empty())
        return str;

    std::size_t firstScan = str.find_first_not_of(' ');
    std::size_t first     = firstScan == std::string::npos ? str.length() : firstScan;
    std::size_t last      = str.find_last_not_of(' ');
    std::cout << "firstScan=" << firstScan << "\n";
    std::cout << "first=" << first << "\n";
    std::cout << "last=" << last << "\n";
    return str.substr(first, last-first+1);
}

int main()
{   
    std::string str{"   "};
    std::cout << "[" << trim( str ) << "]\n";
}