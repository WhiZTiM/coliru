#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

using namespace boost::property_tree;

int main() {
    for (int i = 0; i < 10; i++) {
        try {
            boost::property_tree::ptree pt;
            boost::property_tree::read_json("macAddr.txt", pt);

            BOOST_FOREACH (boost::property_tree::ptree::value_type &v, pt) {
                BOOST_FOREACH (boost::property_tree::ptree::value_type &i, v.second) {
                    std::string s = i.second.get_value("");
                    std::cerr << s << "\n";
                }
                std::cerr << "\n\n";
            }
        } catch (std::exception const &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
