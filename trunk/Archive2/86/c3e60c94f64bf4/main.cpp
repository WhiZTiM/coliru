#include <iostream>
#include <string>
#include <vector>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/find.hpp>
#include <type_traits>
#include <typeinfo>
#include <cstdlib>
#include <ctime>

typedef boost::mpl::vector<int, float, std::string, long> Types;

int main() {
    std::srand(std::time(0));
    boost::mpl::for_each<Types>([i = std::rand() % 4](auto x) {
            if (i == boost::mpl::find<Types, decltype(x)>::type::pos::value) {
                std::cout << typeid(decltype(x)).name();
            }
        });
}
