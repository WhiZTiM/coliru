#include <cstdint>
#include <iostream>

template<typename>
constexpr int my_value = 0;

template<>
constexpr int my_value<int> = -1;

template<>
constexpr int my_value<long> = 100;

int main(){
    std::cout << my_value<float> << std::endl;
    std::cout << my_value<int> << std::endl;
    std::cout << my_value<long> << std::endl;
}
