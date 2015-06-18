#include <boost/range/adaptors.hpp>
#include <iostream>

int main()
{
    using namespace boost::adaptors;

    std::vector<int> input = {10, 20, 30, 40, 50};
    for (auto element : input | indexed(1)) {
        element.value() /= element.index();
    }

    for (int i : input) {
        std::cout << i << ' ';
    }

    return 0;
}
