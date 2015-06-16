#include <iostream>
#include <string>
#include <set>
#include <functional>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>

std::string TrimLeftRight(std::string string_to_trim, char left, char right)
{
    auto is_equal = [](char a, char b) { return a == b; };
    
    using namespace boost::algorithm;
    using std::placeholders::_1;
    
    trim_left_if(string_to_trim, std::bind(is_equal, left, _1));
    trim_right_if(string_to_trim, std::bind(is_equal, right, _1));
    
    return string_to_trim;
}

int main()
{
    std::string track_data{"?12345!"};
    std::cout << TrimLeftRight(track_data, '?', '!') << '\n';
}
