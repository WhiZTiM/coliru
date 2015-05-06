

struct Packet
{
    // Data layout:
    //
    //  METADATA               PACKET DATA        PADDING
    // [............][0000000+-+-+-+-+-+-+-+-+-][000000000]
    //               ^       ^                 ^   ^      
    //               |       |                 |   |                                                    
    // storage ------o       |                 |   |      
    // storage + begin ------o                 |   |      
    // storage + capacity ---------------------o   |
    // storage + end ------------------------------o
    //
    struct Impl
    {
        std::uint8_t* mStorage;
        std::uint16_t mBegin;
        std::uint16_t mEnd;
        std::uint16_t mCapacity;
    };
    
    
    using data_layout = std::tuple<MetaData, std::array<uint8_t, 1514>, std::array<uint8_t, 46>>;
};