#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
using namespace boost::property_tree;

int main()
{
    ptree pt;
    std::istringstream iss("{ \"MyArray\": [ \"value1\", \"value2\" ] }");
    read_json(iss, pt);

    for (auto& entry: pt.get_child("MyArray"))
        std::cout << entry.second.get_value<std::string>() << "\n";
}
