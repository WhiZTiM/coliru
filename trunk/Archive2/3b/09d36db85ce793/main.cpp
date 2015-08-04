#include <cstdint>

int do_move(uint32_t walls, int pos, int move) {
    int pos_offset = 5*move + (move & 1) - 8;
    int idx = pos + pos_offset / 2;
    return walls & (1ull << idx) ? pos + pos_offset : pos;
}
