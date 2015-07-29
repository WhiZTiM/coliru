#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<std::string> array(3, "No");
    std::copy(begin(array), end(array), std::ostream_iterator<std::string>(std::cout, "! "));
}