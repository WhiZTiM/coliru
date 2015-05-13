#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdint>

#pragma pack(1)

struct {
    bool C: 1;
    std::uint16_t R: 5;
    std::uint16_t B: 10;
} fields;

struct{
    std::uint16_t C: 1;
    std::uint16_t R: 5;
    std::uint16_t B: 10;
} BandwidthFields;

int main()
{
    std::cout << sizeof(fields) << " " << sizeof(BandwidthFields) << std::endl;
    
    return 0;
}