#include <iostream>
#include <string>
#include <regex>
 
int main()
{
    std::string str = "zzxayyzz";
    std::regex re1("ZZ.*zz"); // case sensitive
    std::regex re2("ZZ.*zz", std::regex::icase | std::regex::ECMAScript); // insensitive
 
    std::cout << "Searching:\n";
    std::smatch m;
    std::regex_search(str, m, re1);
    std::cout << " sensitive match: " << m[0] << '\n';
    std::regex_search(str, m, re2);
    std::cout << " insensitive match: " << m[0] << '\n';
}