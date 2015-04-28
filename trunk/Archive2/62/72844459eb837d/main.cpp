#include <iostream>
#include <string>
#include <boost/type_traits.hpp>

int main()
{
    std::string a("00000000");
    if( a != "00000000")
    {
        std::cout << "a";
    }
}