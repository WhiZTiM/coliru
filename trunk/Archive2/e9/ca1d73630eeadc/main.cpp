#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <string>
#include <array>
#include <exception>
#include <algorithm>
#include <iostream>

struct not_number_error : std::exception {};
struct not_text_error : std::exception {};

struct number_getter : boost::static_visitor<int> {
    template<typename Type> 
    int operator()(Type const&) const { throw not_number_error(); }

    int operator()(int x) const { return x; }
};

struct text_getter : boost::static_visitor<std::string> {
    template<typename Type> 
    std::string operator()(Type const&) const { throw not_text_error(); }

    std::string operator()(std::string x) const { return x; }
};

using cell = boost::variant<int, std::string>;
using board = std::array<boost::optional<cell>, 100>;

int main() {
    board b;
    b[45] = 42;
    b[78] = 108;
    auto sum = std::accumulate(begin(b), end(b), 0, 
        [](int counter, boost::optional<cell> cell) { 
            return counter + 
                boost::apply_visitor(number_getter(), cell.get_value_or(0));
        }
    );
    std::cout << sum;
}