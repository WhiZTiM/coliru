#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>

using boost::property_tree::ptree;

int main() {
    std::istringstream iss(R"(<A><B><C></C></B></A>)");

    ptree pt;
    read_xml(iss, pt);

    pt.add_child("A.N", pt.get_child("A.B"));
    pt.get_child("A").erase("B");

    write_xml(std::cout, pt);
}
