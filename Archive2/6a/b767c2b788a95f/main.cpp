#include <iostream>
#include <boost/range/irange.hpp>

template <typename T>
auto izrange(T upper) -> decltype(boost::irange(static_cast<T>(0), upper)) {
    return boost::irange(static_cast<T>(0), upper);
}

int main() {
    size_t end = 100;
    for (size_t i : izrange(end))
        std::cout << i << ' ';
}
