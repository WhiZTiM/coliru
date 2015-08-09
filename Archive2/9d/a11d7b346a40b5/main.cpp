#include <iostream>
#include <string>
#include <vector>
#include <iterator>

int main()
{
    char c[] = { 'a', 'b', 'c', 'd' };
    
    std::vector<char> v;
    std::string s;
    
    std::copy(c, c+4, std::back_inserter(v));
    std::copy(c, c+4, std::back_inserter(s));
    std::copy(c, c+4, std::ostream_iterator<char>(std::cout));
}
