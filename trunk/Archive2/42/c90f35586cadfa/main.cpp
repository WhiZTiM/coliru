#include <boost/regex.hpp>
#include <iostream>

int main() 
{
    std::string const line = "P112233";
    boost::regex e("P([0-9]{2})([0-9]{2})([0-9]{2})");
    boost::smatch match;

    if (boost::regex_search(line, match, e))
    {
        std::string s0 = match[0].str();
        std::string s1 = match[1].str();
        std::string s2 = match[2].str();
        std::string s3 = match[3].str();

        std::cout << match[0] << std::endl; // prints whole string
        std::cout << s1 << ", " << s2 << ", " << s3 << std::endl;
    }
}
