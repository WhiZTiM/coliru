#include <iostream>
#include <boost/range/irange.hpp>

int main() {
    size_t end = 100;
    for (size_t i : boost::irange(0ul, end))
        std::cout << i << ' ';

    return 0;
}
