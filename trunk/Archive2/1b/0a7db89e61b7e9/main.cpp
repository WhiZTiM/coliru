#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/filesystem.hpp>

#include <iostream>

using namespace boost::property_tree;
namespace fs = boost::filesystem;

namespace project_definition {
    void apply(ptree const& def, fs::path const& rootFolder) {
        for (auto node : def) {
            if ("folder" == node.first) {
                fs::path where = rootFolder / node.second.get<std::string>("name");
                fs::create_directories(where);

                apply(node.second, where);
            }
            if ("file" == node.first) {
                std::ofstream((rootFolder / node.second.get<std::string>("name")).native(), std::ios::trunc);
            }
        }
    }
}

int main()
{
    ptree projdef;
    read_xml("input.txt", projdef);

    project_definition::apply(projdef, "./rootfolder/");
}

