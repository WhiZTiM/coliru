#include <iostream>
#include <boost/icl/split_interval_map.hpp>
#include <boost/icl/interval_map.hpp>
namespace icl = boost::icl;

template <typename Map> void test() {
    std::cout << __PRETTY_FUNCTION__ << ":\n";

    Map s { { Map::interval_type::right_open(2,10), 3 } };
    std::cout << s << "\n";

    s.add({ {10,12}, 3 });
    std::cout << s << "\n";
}

int main()
{
    test<icl::interval_map<int, int> >();
    test<icl::split_interval_map<int, int> >();
}
