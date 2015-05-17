#include <iostream>
#include <stdint.h>
#include <limits>
#include <limits.h>
#include <locale>
#include <iomanip>
int main()
{
    union variant_type {
        uint8_t  u8_data[8];
        uint16_t u16_data[4];
        uint32_t u32_data[2];
        uint64_t u64_data[1];
        
        explicit variant_type(const uint8_t & v)
        {
            u64_data[0] = 0;
            u8_data[7]  = v;
        }
        
        explicit variant_type(const uint16_t & v)
        {
            u64_data[0] = 0;
            u16_data[3] = v;
        }
        
        explicit variant_type(const uint32_t & v)
        {
            u64_data[0] = 0;
            u32_data[1] = v;
        }
        
        explicit variant_type(const uint64_t & v)
        {
            u64_data[0] = v;
        }
    };
    
    struct uuid_type
    {
        const uint64_t version_mask   = 0xFFFFFFFFFFFFFF0F;
        const uint16_t variant_mask   = 0xFF3F;
        const uint8_t  multicast_mask = 0xFE;
       
        variant_type lo;
        variant_type hi;
       
       uint64_t get_timestamp() const
       {
           return (lo.u64_data[0] & version_mask);
       }
       
       uint8_t get_version() const
       {
           return (lo.u64_data[0] & (~version_mask));
       }
       
       uint64_t get_node() const
       {
           variant_type type;
           
           type.u16_data[0] = hi.u16_data[1];
           type.u16_data[1] = hi.u16_data[2];
           type.u16_data[2] = hi.u16_data[3];
           type.u16_data[3] = 0;
          
           return type.u64_data[0];
       }
       
       void set_timestamp(const uint64_t timestamp)
       {
           timestamp &= version_mask;
           timestamp |= (get_version() & (~version_mask));
    
           lo.u64_data[0] = timestamp;
       }
       
       void set_version(const uint8_t version)
       {
           uint64_t timestamp = get_timestamp();
           timestamp &= version_mask;
           timestamp |= (version & (~version_mask));
    
           lo.u64_data[0] = timestamp;
       }
       
       void set_node(const uint64_t & v)
       {
           variant_type type(v);
           type.u64_data[0] = v;
           type.u16_data[3] = 0;
           
           hi.u16_data[1] = type.u16_data[0];
           hi.u16_data[2] = type.u16_data[1];
           hi.u16_data[3] = type.u16_data[2];
       }
       
       uint8_t get_variant() const
       {
           return (hi.u16_data[0] & (~variant_mask));
       }
       
       uint16_t get_sequence() const
       {
           return (hi.u16_data[0] & (variant_mask));
       }
       
       void set_sequence(const uint16_t sequence)
       {
           sequence &= variant_mask;
           sequence |= (get_variant() & (~variant_mask));
               
           hi.u16_data[0] = sequence;
       }
       
       void set_variant(const uint8_t variant)
       {
           uint16_t sequence = get_sequence();
           sequence &= variant_mask;
           sequence |= (variant & (~variant_mask));
               
           hi.u16_data[0] = sequence;
       }
    };
    
    uuid_type uuid;
    // 0..3 time-low                 = 4hexOctet
    // 4..5 time-mid                 = 2hexOctet
    // 6..7 time-high-and-version    = 2hexOctet
    // 8 clock-seq-and-reserved      = hexOctet
    // 9 clock-seq-low               = hexOctet
    // 10..15 node                   = 6hexOctet  
    uint64_t timestamp = 0;
    uint8_t  version   = 4<<4;
    uint16_t sequence  = 0;
    uint8_t  variant   = 2<<6;
    variant_type node;
    
    node.u8_data[0] = 'R';
    node.u8_data[1] = 'A';
    node.u8_data[2] = 'N';
    node.u8_data[3] = 'D';
    node.u8_data[4] = 'O';
    node.u8_data[5] = 'M';
    node.u8_data[6] = '0';
    node.u8_data[7] = '0';
    
    uint8_t  multicast = 1<<0;
        
    // 60 bit timestamp | 4 bit version
    uint64_t version_mask = 0xFFFFFFFFFFFFFF0F;
    timestamp &= version_mask;
    timestamp |= (version & (~version_mask));
    
    // 14 bit sequence | 2 bit variant 
    uint16_t variant_mask = 0xFF3F;
    sequence &= variant_mask;
    sequence |= (variant & (~variant_mask));

    // set the multicast bit on the node id
    uint8_t multicast_mask = 0xFE;
    node[0] &= multicast_mask;
    node[0] |= (multicast & (~multicast_mask));
    
    
    uuid.lo.u64_data[0] = timestamp;
    uuid.hi.u16_data[0] = sequence;
    uuid.hi.u16_data[1] = node.u16_data[0];
    uuid.hi.u16_data[2] = node.u16_data[1];
    uuid.hi.u16_data[3] = node.u16_data[2];
    
    
    std::cout << "Timestamp: " << std::setfill('0') 
                         << std::setw(16)
                         << std::hex
                         << (uuid.lo.u64_data[0] & version_mask) << "\n";
                         
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
    
   std::cout << "Multicast: " << std::setfill('0')
                         << std::setw(2)
                         << std::hex
                         << static_cast<uint16_t>(node[0] & (~multicast_mask)) << "\n";

    return 1;
}