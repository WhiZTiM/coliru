#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <fstream>
#include <iostream>

using boost::property_tree::ptree;

int main() {

    std::fstream ifs("input.txt");
    ptree pt;

    read_ini(ifs, pt);

    // let's get just the section2
    
    if (boost::optional<ptree&> oops = pt.get_child_optional("oops")) {
        std::cout << "There is a section `oops`\n";
    } else {
        std::cout << "There is NO section `oops`\n";
    }

    ptree& section2 = pt.get_child("section2"); // we want the CCs!
    for (auto& entry : section2)
    {
        std::cout << entry.first << "\thas value '" << entry.second.get_value("") << "'\n";
    }

    write_ini(std::cout, section2);
}
