#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <fstream>

int main()
{
    using namespace boost::property_tree;

    ptree pt;
    read_json(std::cin, pt);

    for (auto& challenge : pt.get_child("challenges"))
        for (auto& prop : challenge.second)
            std::cout << prop.first << ": " << prop.second.get_value<std::string>() << "\n";
}
