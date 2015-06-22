#include <boost/lexical_cast.hpp>
#include <iostream>

int main()
{
    std::size_t original = 9999999;
    auto sz = boost::lexical_cast<size_t>(std::to_string(original));
    std::cout << sz << "\n";
    sz = boost::lexical_cast<size_t>(std::to_string(original+1));
    std::cout << sz << "\n";
}