#include <tuple>

template<typename ... Types, typename ... Args>
auto method(Args &&... args){
    return std::tuple<Types...>{};
}

int main(){
    auto my_tuple = method<int, float, short, float, double>(1.f, 2.0);
}
