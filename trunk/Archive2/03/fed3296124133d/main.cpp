#include <iostream>
#include <vector>

#include <boost/container/flat_map.hpp>

struct foo {
    foo(size_t size) {
        bar.reserve(size);
    }
        
    boost::container::flat_map<int, int> bar;
};

int main() {
    auto the_size = 30;
    auto foos = std::vector<foo>();
    
    for (int i = 0; i < 3; ++i) {
        foos.emplace_back(the_size);
    }
    
    for (auto&& foo : foos) {
        std::cout << foo.bar.capacity() << std::endl;
    }
}