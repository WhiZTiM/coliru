#include <cstdint>

std::uint32_t f(std::uint32_t n, std::uint32_t p) 
{
    auto m = n%p;
    if (m < p/2) {
        return (m==0)*p+2*m-1;
    }
    return p-2*(p-m)-1;
}

#include <iostream>
int main() {
    std::cout << f(4294967295U, 4294967291U) << ' ' << f(4294967291U, 4294967295U) << ' ' << f(5, 5);
}