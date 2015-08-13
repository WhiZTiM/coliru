#include <iostream>
#include <memory>
#include <map>
#include <boost/variant.hpp>

int main()
{
    boost::variant<int, char> v;
    std::cout << typeid(v).name() << std::endl;
    char& ch = boost::get<char>(v);
    ch = 5;
    std::cout << boost::get<char>(v) << std::endl;
    return 0;
}
