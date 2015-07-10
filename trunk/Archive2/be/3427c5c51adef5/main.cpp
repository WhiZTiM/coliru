#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

namespace pt = boost::property_tree;

std::string ss = "{ \"item1\" : 123, \"item2\" : 456, \"item3\" : 789 }";

int main()
{
    // Read json.
    pt::ptree pt2;
    boost::iostreams::array_source as(&ss[0], ss.size());
    boost::iostreams::stream<boost::iostreams::array_source> is(as);

    pt::read_json(is, pt2);
    std::cout << "item1 = \"" << pt2.get<std::string>("item1") << "\"\n";
    std::cout << "item2 = \"" << pt2.get<std::string>("item2") << "\"\n";
    std::cout << "item3 = \"" << pt2.get<std::string>("item3") << "\"\n";
}