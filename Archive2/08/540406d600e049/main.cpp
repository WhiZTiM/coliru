#include <algorithm>
#include <iostream>
#include <iterator>
#include <functional>
#include <random>

int main() {
    using IntType = uint16_t;
    
    std::random_device rd;
    std::uniform_int_distribution<IntType> dist{1, 50};
    
    std::generate_n(std::ostream_iterator<IntType>{std::cout, " "}, 20, 
            std::bind(dist, std::ref(rd)));
}
