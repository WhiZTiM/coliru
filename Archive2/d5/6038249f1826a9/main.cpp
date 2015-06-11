#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <limits>
#include <functional>
#include <random>
#include <string>
#include <vector>

template<typename T, size_t size>
std::ostream& operator<<(std::ostream& os, const std::array<T, size>& arr) {
    for (auto& el : arr) {
        os << el << ' ';
    }
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    for (auto& el : vec) {
        os << el << ' ';
    }
    return os;
}

int main() {
    using IntType = int16_t;
    
    std::array<IntType, 20> E;
    
    std::random_device rd;
    std::uniform_int_distribution<IntType> dist{
        std::numeric_limits<IntType>::min(),
        std::numeric_limits<IntType>::max()};
    
    std::generate(std::begin(E), std::end(E), std::bind(dist, std::ref(rd)));
    
    std::cout << "Array E: " << E << std::endl;
    
    
    std::vector<IntType> F;
    auto is_positive = [](auto a) { return a > 0; };
    auto is_even     = [](auto a) { return !(a & 1); };
    
    std::copy_if(std::next(std::max_element(E.cbegin(), E.cend())), E.cend(),
            std::copy_if(E.cbegin(), std::min_element(E.cbegin(), E.cend()),
                    std::back_inserter(F), is_positive), is_even);
        
    std::cout << "Array F: " << F << std::endl;
}
