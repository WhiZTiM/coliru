#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using boost::property_tree::ptree;

int main()
{
    ptree pt;
    pt.put("a.b", 1.0);
    pt.put("a.c", 2.0);
    pt.put("b.g", 3.0);

        ptree pt2;
        pt2.add_child("a", pt.get_child("a"));

    auto xws = boost::property_tree::xml_writer_make_settings<std::string>(' ',1);
    boost::property_tree::write_xml(std::cout, pt2, xws);
}
