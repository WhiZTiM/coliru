#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <string>
#include <array>
#include <exception>
#include <algorithm>
#include <iostream>

struct not_number_error : std::exception {};
struct not_text_error : std::exception {};

template<typename Type, typename Except>
struct element_getter : boost::static_visitor<Type> {
    template<typename Other>
    Type operator()(Other const&) const { throw Except(); }
    
    Type operator()(Type const& x) const { return x; }
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
                boost::apply_visitor(
                    element_getter<int, not_number_error>(), 
                    cell.get_value_or(0)
                );
        }
    );
    std::cout << sum;
}