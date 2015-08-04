#include <cstdint>

int do_move(uint32_t walls, int pos, int move) {
    int idx = pos + move / 2;
    return walls & (1ull << idx) ? pos + move : pos;
}
