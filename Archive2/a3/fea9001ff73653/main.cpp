#include <iostream>
#include <string>
#include <vector>
#include <boost/container/string.hpp>

int main()
{
    boost::container::basic_string<char> my_basic_string("abc\0def");
    std::string s(my_basic_string.data(), my_basic_string.size());
    std::string s2(my_basic_string.begin(), my_basic_string.end());
    
    std::cout << s.size() << " " << s << std::endl;
    std::cout << s2.size() << " " << s2 << std::endl;
}
