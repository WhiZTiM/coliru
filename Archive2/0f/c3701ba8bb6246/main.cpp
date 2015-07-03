#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>

#include <boost/phoenix.hpp>

using namespace boost;
using namespace boost::phoenix::arg_names;

#include <iostream>

int main() {
    tuple<int, double, std::string> demo(42, 3.1415, "hello pie universe");

    fusion::for_each(demo, std::cout << arg1 << "\n");

    auto& v2 = get<1>(demo);
    v2 *= 10;
    std::cout << "\nNew v2: "         << v2   << "\n";
    std::cout << "Tuple after edit: " << demo << "\n";
}
