#include <boost/regex.hpp>
#include <iostream>

int main() 
{
    std::string const line = "P112233";
    boost::regex e("P([0-9]{2})([0-9]{2})([0-9]{2})");
    boost::smatch match;

    if (boost::regex_search(line, match, e))
        std::cout << match[1] << ", " << match[2] << ", " << match[3] << std::endl;
}
