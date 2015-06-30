#include <iostream>
#include <string>
#include <boost/container/string.hpp>

int main()
{
    boost::container::basic_string<char> my_basic_string("abc\0def", 7);
    std::string s(my_basic_string.data(), my_basic_string.size());
    std::string s2(my_basic_string.begin(), my_basic_string.end());
    
    std::cout << s.size() << " " << s << std::endl;
    std::cout << s2.size() << " " << s2 << std::endl;
    std::cout << my_basic_string.size() << " " << my_basic_string << " " << my_basic_string.data() << std::endl;
}