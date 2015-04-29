#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>

struct base {};

struct derived : base
{
    std::uint16_t m = 0xFFFF;
};

int main()
{
    derived dst;
    base src{};
    
    std::cout << dst.m << "\n";
    
    base& ebo = dst;
    
    std::memcpy(&ebo, &src, sizeof(src));
    
    std::cout << dst.m << "\n";
}