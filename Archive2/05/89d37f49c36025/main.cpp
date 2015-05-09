#include <iostream>

template<typename... Ts>
auto foo(Ts... ts) {
    return ((ts + 1) * ...); 
}

int main() {
    std::cout << foo(5, 2, 9); //(5+1) * (2+1) * (9+1) = 6*3*10 = 180
}