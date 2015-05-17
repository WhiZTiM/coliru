#include <iostream>
#include <stdint.h>
#include <limits>
#include <limits.h>
#include <locale>
#include <iomanip>
int main()
{
    uint8_t uuid[16] = {0};
    
    // 0..3 time-low                 = 4hexOctet
    // 4..5 time-mid                 = 2hexOctet
    // 6..7 time-high-and-version    = 2hexOctet
    // 8 clock-seq-and-reserved      = hexOctet
    // 9 clock-seq-low               = hexOctet
    // 10..15 node                   = 6hexOctet  
    uint64_t timestamp = 0;
    uint8_t  version   = 1<<6;
    uint16_t sequence  = 0;
    uint8_t  variant   = 1<<7;
    uint8_t  node[6]   = {0,0,0,0,0,0};
        
    // 60 bit timestamp | 4 bit version
    uint64_t version_mask = 0xFFFFFFFFFFFFFF0F;
    timestamp &= version_mask;
    timestamp |= (version & (~version_mask));
    
    // 14 bit sequence | 2 bit variant 
    uint16_t variant_mask = 0xFF3F;
    sequence &= variant_mask;
    sequence |= (variant & (~variant_mask));
        
    *((uint64_t *)&uuid[0]) = timestamp;
    *((uint16_t *)&uuid[8]) = sequence;
    *((uint16_t *)&uuid[10]) = *((uint16_t *)&node[0]);
    *((uint32_t *)&uuid[12]) = *((uint32_t *)&node[2]);
    
    std::cout << "Timestamp: " << std::setfill('0') 
                         << std::setw(16)
                         << std::hex
                         << (timestamp & version_mask) << "\n";
                         
    std::cout << "Version: " << std::setfill('0') 
                         << std::setw(2)
                         << std::hex
                         << (timestamp & (~version_mask)) << "\n";
                         
    std::cout << "Sequence: " << std::setfill('0')
                         << std::setw(8)
                         << std::hex
                         << (sequence & variant_mask) << "\n";

   std::cout << "Variant: " << std::setfill('0')
                         << std::setw(2)
                         << std::hex
                         << (sequence & (~variant_mask)) << "\n";

    std::cout << "Node: " << std::setfill('0')
                         << std::setw(4)
                         << std::hex
                         << *((uint16_t *)&node[0])
                         << std::setfill('0')
                         << std::setw(8)
                         << std::hex
                         << *((uint32_t *)&node[2]) << "\n";
    
    return 1;
}