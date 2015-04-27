#include <utility>
#include <cstdint>

__attribute__((used)) inline std::pair<uint64_t, uint64_t> mulu64(uint64_t a, uint64_t b) {
    uint64_t h, l;
    asm("mulq %3"
        : "=a"(l),"=d"(h)
        : "a"(a), "rm"(b)
        : "cc");
    return std::make_pair(h, l);
}

__attribute__((used)) inline std::pair<uint64_t, uint64_t> mulu64_int(uint64_t a, uint64_t b) {
    unsigned __int128 r = a;
    r *= b;
    return std::make_pair(r >> 64, r & uint64_t(-1));
}