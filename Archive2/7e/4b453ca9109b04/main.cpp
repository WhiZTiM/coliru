#include <cstdint>
#include <bitset>

int popcnt(uint64_t x) { return std::bitset<64>(x).count(); }