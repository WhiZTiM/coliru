#include <iostream>
#include <limits>
#include <type_traits>
#include <cstdint>

auto a = std::numeric_limits<long>::min();

template <typename T, typename U>
void f(){
    static_assert(std::is_signed<T>::value, "not bright");
    
    U absMin = std::numeric_limits<T>::min();
    std::cerr << absMin << std::endl;
    std::cerr << -absMin << std::endl;
}

int main(int ,char**)
{
     
    f<int8_t, uint8_t>(); 
}
