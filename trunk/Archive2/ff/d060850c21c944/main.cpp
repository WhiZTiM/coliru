#include <iostream>
#include <bitset>
#include <cstdint>

using u64 = std::uint64_t;

// See http://graphics.stanford.edu/~seander/bithacks.html#NextBitPermutation
u64 next(u64 v) {
    u64 t = v | (v - 1);
    return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
}

// Or without __builtin_ctz: (Slightly slower.)
//u64 next(u64 v) {
//    u64 t = (v | (v - 1)) + 1;
//    return t | ((((t & -t) / (v & -v)) >> 1) - 1);
//}

constexpr u64 N = 10;
constexpr u64 M = 5;

int main() {
    u64 x = (1l << M) - 1;
    while (x) {
       std::cout << std::bitset<N>(x) << std::endl;
       x = next(x) & ((1l << N) - 1);
    }
}