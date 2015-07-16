#include <cstdint>


// Mark a memory address as allocated by unsetting
// the corresponding bit in the bit-map.
void bit_allocate(uint64_t& bitmap, uint64_t pos)
{
    uint64_t mask = 1ul << pos;
    mask = ~mask;
    bitmap &= mask;
}

// Mark a memory address as free by setting
// the corresponding bit in the bit-map.
void  bit_free(uint64_t& bitmap, uint64_t pos) throw()
{
    uint64_t mask = 1ul << pos;
    bitmap |= mask;
}


// Find the position of the first non-zero bit.
uint64_t bit_scan_forward(uint64_t num)
{
    return static_cast<uint64_t>(__builtin_ctzll(num));
}


#include <iostream>
#include <iomanip>


int main()
{
    uint64_t bitmap = -1;
    std::cout << std::hex << std::setw(16) << std::setfill('0') << bitmap << " first free: " << std::dec << bit_scan_forward(bitmap) << std::endl;
    
    for (auto i = 0ul; i != 64; ++i)
    {
        uint64_t position = bit_scan_forward(bitmap);
        bit_allocate(bitmap, position);
        std::cout << std::hex << std::setw(16) << std::setfill('0') << bitmap << " first free: " << std::dec << bit_scan_forward(bitmap) << std::endl;
    }
    
    std::cout << "++++++++++++++++" << std::endl;
    
    for (auto i = 0ul; i != 64; ++i)
    {
        bit_free(bitmap, i);
        std::cout << std::hex << std::setw(16) << std::setfill('0') << bitmap << " first free: " << std::dec << bit_scan_forward(bitmap) << std::endl;
    }
}
