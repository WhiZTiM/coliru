#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <functional>
#include <random>
#include <string>

template<typename T, size_t size>
std::ostream& operator<<(std::ostream& os, const std::array<T, size>& arr) {
    for (auto& el : arr) {
        os << el << ' ';
    }
    return os;
}

int main() {
    using IntType = int16_t;
    
    std::array<IntType, 20> E;
    
    std::random_device rd;
    std::uniform_int_distribution<IntType> dist{1, 50};
    
    std::generate(std::begin(E), std::end(E), std::bind(dist, std::ref(rd)));
    
    std::cout << E << std::endl;
}
