#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string/join.hpp>
#include <boost/range/adaptor/transformed.hpp>

int main()
{
    const auto message = boost::algorithm::join(
        std::string("iuuq;00kbwbdpefs/ojokb") 
            | boost::adaptors::transformed([](char c) { return c - 1; })
            | boost::adaptors::transformed([](char c) { return std::string(1, c); })
        , "\n"); 
    std::cout << message << std::endl;
}
