#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>

int main()
{
    std::istringstream f1 {"1 4 5 18"};
    std::istringstream f2 {"2 3 15 16"};
    std::ostringstream out;
    std::merge(std::istream_iterator<int>(f1), std::istream_iterator<int>(),
               std::istream_iterator<int>(f2), std::istream_iterator<int>(),
               std::ostream_iterator<int>(out, ", "));
    std::cout << out.str();
}