#include <iostream>
#include <algorithm>
#include <iterator>

template<typename It>
void fn1(It begin, It end) {
    using value_type = typename It::value_type;
    std::ostream_iterator<value_type> out(std::cout, ", ");
    std::copy(begin, end - 1, out);
    std::cout << *(end - 1);
}

auto fn2 = [](auto begin, decltype(begin) end) {
    using value_type = typename decltype(begin)::value_type;
    std::ostream_iterator<value_type> out(std::cout, ", ");
    std::copy(begin, end - 1, out);
    std::cout << *(end - 1);
};

int main() {
    std::vector<int> x {1, 2, 3, 4};
    fn1(begin(x), end(x));
    std::cout << '\n';
    fn2(begin(x), end(x));
}