#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

template <class Comp>
std::function<typename Comp::result_type (typename Comp::first_argument_type)> predicate(typename Comp::second_argument_type rhs)
{
    return [rhs](typename Comp::first_argument_type lhs){
        Comp c{};
        return c(lhs, rhs);
    };
}

int main() {
    std::vector<int> v {1, 2, 3, 4, 5};
    
    v.erase(std::remove_if(begin(v), end(v), predicate<std::less<int>>(4)), end(v));
    
    std::copy(begin(v), end(v), std::ostream_iterator<int>(std::cout, " "));
}