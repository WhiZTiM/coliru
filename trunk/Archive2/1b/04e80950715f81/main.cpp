#include <iostream>

int main(){
    
    auto unit = [](auto x) {
    return [=](){ return x; };
    };
    
    std::cout << unit(7)() << "\n";
}