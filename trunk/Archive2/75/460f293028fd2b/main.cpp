#include <boost/regex.hpp>
#include <iostream>

int main() 
{
    std::string const line = "P112233";
    boost::regex e("P([0-9]{2})([0-9]{2})([0-9]{2})");
    boost::smatch match;

    if (boost::regex_search(line, match, e))
    {
        std::string s1 = match[1], s2 = match[2], s3 = match[3];

        std::cout << s1 << ", " << s2 << ", " << s3 << std::endl;
    }
}
