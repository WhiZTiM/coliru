#include <iostream>
#include <string>
#include <boost/container/string.hpp>

int main()
{
    boost::container::basic_string<char> my_basic_string("hello world!");
    std::string s(my_basic_string.c_str());
    std::cout << s << std::endl;
}
