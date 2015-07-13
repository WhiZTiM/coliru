#define BOOST_NO_EXCEPTIONS
#include <iostream>
#include <boost/property_tree/ini_parser.hpp>

namespace boost {
    void throw_exception(std::exception const& e) {
        std::cerr << "Fake exception: " << e.what() << "\n";
        std::exit(255);
    }
}

using namespace boost::property_tree;

int main() {
    ptree pt;
    read_ini(std::cin, pt);

    write_ini(std::cout, pt.get_child("section5"));
}
