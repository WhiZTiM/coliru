#include <iostream>
#include <boost/range/irange.hpp>

int main() {
    for (size_t i : boost::irange(0, 100))
        std::cout << i << ' ';

    return 0;
}
