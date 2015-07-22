#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>

using boost::property_tree::ptree;

int main() {

    ptree pt;
    pt.push_back(ptree::value_type("pi", ptree("3.14159")));
    pt.put("pi.<xmlattr>.id", "pi_0");

    write_xml(std::cout, pt);
}
