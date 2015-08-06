#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v {1, 2, 3};
    std::vector<int> v2;
    
    v2.reserve(v.size() * v.size());
    auto ite = std::back_inserter(v2);
    for(auto i1 : v)
        for(auto i2 : v)
            *ite++ = i1 - i2;
    swap(v, v2);
    
    std::copy(begin(v), end(v), std::ostream_iterator<int>(std::cout, " "));
}