#include <random>
#include <limits>
#include <cstddef>
#include <iostream>
#include <algorithm>

template <typename T>
T getRandom()
{
    uint8_t* t_as_uint8 = static_cast<uint8_t*>(malloc(sizeof(T)));
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<uint8_t> distribution;
    std::generate(t_as_uint8, t_as_uint8 + sizeof(T), [&] () {return distribution(generator); });
    return *(reinterpret_cast<T*>(t_as_uint8));
}

int main()
{   
    std::cout << getRandom<int>() << std::endl;

    return 0;
}