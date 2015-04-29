#include<iostream>
#include<limits>

int main(){
    constexpr float f = float(std::numeric_limits<unsigned long long>::max());
    constexpr unsigned long long l = (unsigned long long) f;
    std::cout << l << std::endl;
}