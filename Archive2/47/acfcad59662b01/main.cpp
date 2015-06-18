#include <boost/range/adaptors.hpp>
#include <iostream>

int main()
{
    using namespace boost::adaptors;

    std::vector<int> input = {10, 20, 30, 40, 50};
    for (auto element : input | indexed(0)) {
        element.value() /= 1+element.index();
    }

    for (int i : input) {
        std::cout << i << ' ';
    }

    return 0;
}
