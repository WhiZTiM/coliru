#include <iostream>
#include <vector>
#include <boost/range/counting_range.hpp>

int main() {
    std::vector<int> v{1,2,3};
   
    for(auto it: boost::counting_range(v.begin(), v.end())) {
       std::cout << *it;
    }
    std::cout << '\n';
}