#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <iostream>
#include <sstream>
namespace pt = boost::property_tree;

int main() {   
    std::string x = "{\"value\": nan}";
    std::istringstream is{x};
    pt::ptree tree;
    pt::read_json(is, tree);
}