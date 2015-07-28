#include <iostream>
#include <vector>
#include <boost/range/counting_range.hpp>

template<class C>
auto iterators_into( C&& c ) {
    using std::begin; using std::end;
    return boost::counting_range(begin(c), end(c));
}

int main() {
    std::vector<int> v{1,2,3};
   
    for(auto it: iterators_into(v)) {
       std::cout << *it;
    }
    std::cout << '\n';
}