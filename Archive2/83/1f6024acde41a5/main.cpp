#include <tuple>
#include <iostream>

template <typename... Ts> void TD() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

template<typename ... Types, typename ... Args>
auto method(Args &&... args){
    return std::tuple<Types...>{};
}

int main(){
    auto my_tuple = method<int, float, short, float, double>(1.f, 2.0);
    
    TD<decltype(my_tuple)>();
}
