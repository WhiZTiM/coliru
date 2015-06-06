#include <array>
#include <cstring>
#include <cstdint>


using LocalPort = uint16_t;
using RemotePort = uint16_t;

using LocalIP = std::array<uint8_t, 16>;
using RemoteIP = std::array<uint8_t, 16>;






struct TCPSessionKey_V6
{
    TCPSessionKey_V6(LocalPort local_port, RemotePort remote_port, LocalIP local_ip, RemoteIP remote_ip) :
        ports((local_port << 16) | remote_port)
    {
        auto dst = reinterpret_cast<char*>(&ip[0]);
        std::memcpy(dst, &local_ip, sizeof(local_ip));
        dst += sizeof(local_ip);
        std::memcpy(dst, &remote_ip, sizeof(remote_ip));
    }
    
    friend bool operator<(const TCPSessionKey_V6& lhs, const TCPSessionKey_V6& rhs)
    {
        if (lhs.ports != rhs.ports)
        {
            return lhs.ports < rhs.ports;
        }
        
        if (lhs.ip[1] != rhs.ip[1])
        {
            return lhs.ip[1] < rhs.ip[1];
        }
        
        if (lhs.ip[3] != rhs.ip[3])
        {
            return lhs.ip[3] < rhs.ip[3];
        }
        
        // Finally check most significant bits.
        if (lhs.ip[0] != rhs.ip[0])
        { return lhs.ip[0] < rhs.ip[0]; }
        
        return lhs.ip[2] < rhs.ip[2];
    }
    
    
    uint32_t ports;
    uint64_t ip[4];
};




