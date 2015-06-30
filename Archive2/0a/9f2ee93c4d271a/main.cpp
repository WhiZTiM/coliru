// Compile on a recent version of clang and run it:
// clang++ -std=c++11 -O3 -Wall -fsanitize=undefined main.cpp -o stdint16 && ./stdint16
// g++ -std=c++11 -O3 -Wall -ftrapv main.cpp -o stdint16 && ./stdint16
//
#include <cinttypes>
#include <cstdint>
#include <cstdio>

int main()
{
    /*
     * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3337.pdf
     *
     * 3.9.1 Fundamental types [basic.fundamental]
     *
     */
    uint16_t b = UINT16_MAX; b = b * b; // Standard says this is defined, and modulo 2^16

    std::printf(" %04" PRIX16 "\n", b );

    int64_t c = b * b;
    
    std::printf(" %ld\n", c );
    
    return 0;
}