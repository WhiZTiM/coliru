#include <cstdint>


int alignment(void* ptr)
{
    auto b = reinterpret_cast<std::uintptr_t>(ptr);
    
    auto b1 = b & 0x1;
    auto b2 = b & 0x2;
    auto b4 = b & 0x4;
    
    
    auto align16 = !b1;
    auto align32 = !(b1 | b2);
    auto align64 = !(b1 | b2 | b4);
    
    auto result = 1 + align16;
    result += 2 * (align16 & align32);
    result += 4 * (align16 & align32 & align64);
    return result;
}


#ifndef ASM_ONLY
#include <iostream>

int main()
{
    char c[8];
    std::cout << alignment(&c[0]) << std::endl;
    std::cout << alignment(&c[1]) << std::endl;
    std::cout << alignment(&c[2]) << std::endl;
    std::cout << alignment(&c[3]) << std::endl;
    std::cout << alignment(&c[4]) << std::endl;
    std::cout << alignment(&c[5]) << std::endl;
    std::cout << alignment(&c[6]) << std::endl;
    std::cout << alignment(&c[7]) << std::endl;
}
#endif