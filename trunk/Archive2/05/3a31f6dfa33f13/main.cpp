#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

template <class Comp>
auto predicate(typename Comp::second_argument_type rhs) {
    return [c = Comp{}, rhs](typename Comp::first_argument_type lhs) {
        return c(lhs, rhs);
    };
}

int main() {
    std::vector<int> v {1, 2, 3, 4, 5};
    
    v.erase(std::remove_if(begin(v), end(v), predicate<std::less<int>>(4)), end(v));
    
    std::copy(begin(v), end(v), std::ostream_iterator<int>(std::cout, " "));
}