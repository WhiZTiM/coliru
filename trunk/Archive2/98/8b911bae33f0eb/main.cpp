#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/include/copy.hpp>
#include <iostream>

using namespace boost;

int main()
{
    std::string thickLine, thinLine;
    auto y = std::tie(thinLine, thickLine);
    fusion::copy(fusion::transform(std::make_tuple('-', '='), [](auto ch){return std::string(80, ch);}), y);
    
    std::cout << thickLine << "\n" << thinLine << "\n";
}