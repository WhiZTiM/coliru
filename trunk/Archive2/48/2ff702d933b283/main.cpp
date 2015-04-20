#include <cstdint>
#include <algorithm>

std::uint32_t f(std::uint32_t n, std::uint32_t p) 
{
    return (2*std::min(p-n%p, n%p)-1)%p;
}

#include <iostream>
int main() {
    std::cout << f(4294967295U, 4294967291U) << ' ' << f(4294967291U, 4294967295U);
}