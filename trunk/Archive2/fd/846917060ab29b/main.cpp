#include <array>
#include <cassert>
#include <cstdint>
#include <vector>


enum struct EtherType : uint16_t { ARP, IPv4, IPv6 };

struct MACAddress
{
    std::array<uint8_t, 6> mData;
};


struct IPv4Address
{
    std::array<uint8_t, 4> mData;
};


struct IPv6Address
{
    std::array<uint8_t, 16> mData;
};


struct EthernetHeader
{
    MACAddress mDestination;
    MACAddress mSource;
    EtherType mEtherType;
};


struct IPv4Header
{
    IPv4Address mSource;
    IPv4Address mDestination;
};


struct IPv6Header
{
    IPv6Address mSource;
    IPv6Address mDestination;
};


enum struct IPProtNum : uint8_t
{
    TCP,
    UDP,
    ICMP
};


struct Packet
{
    EtherType getEtherType() { return EtherType::IPv4; }
    IPProtNum getProtocol() const { return IPProtNum::TCP; }
    
};


struct Stack;



struct TCPProtocol
{
    static bool receive(Stack&, Packet) { return true; }
};

struct UDPProtocol
{
    static bool receive(Stack&, Packet) { return true; }
};

struct ICMPProtocol
{
    static bool receive(Stack&, Packet) { return true; }
};


struct Stack
{
    struct BadMTU : virtual std::exception
    {
        BadMTU(uint16_t mtu) : mtu(mtu) {}
        uint16_t mtu;
    };
    
    Stack(uint16_t mtu)
    {
        mBuffer.resize(mtu);
        if (mtu < sizeof(EthernetHeader))
        {
            throw BadMTU(mtu);
        }
        
        addHeader(FixAlignment()); // 2 bytes + 14-bytes of Ethernet header => 4-byte alignment for L3/L4 which is nice.
        mEthernetHeader = &addHeader(EthernetHeader());
    }
    
    void set_mac(MACAddress mac)
    {
        mEthernetHeader->mDestination = mac;
    }
    
    void set_ip4()
    {
        if (mIPv6Header) throw std::runtime_error("It's already IPv6");
        mIPv4Header = &addHeader(IPv4Header());
        update_receive_function();
    }
    
    void set_ip6()
    {
        if (mIPv4Header) throw std::runtime_error("It's already IPv4");
        mIPv6Header = &addHeader(IPv6Header());
        update_receive_function();
    }
    
    void enable_tcp()
    {
        mCommonProtocols |= TCP;
        update_receive_function();
    }
    
    void enable_udp()
    {
        mCommonProtocols |= UDP;
        update_receive_function();
    }
    
    // Can also be used for VLAN, PPP or something else.
    template<typename Header>
    Header& addHeader(Header header)
    {
        // Check alignment of storage against that of the header.
        
        assert(reinterpret_cast<long>(mBuffer.data()) % alignof(Header) == 0);
        assert(mCumulativeHeaderSize % alignof(Header) == 0);
        
        auto result = new (mBuffer.data() + mCumulativeHeaderSize) Header(header);
        mCumulativeHeaderSize += sizeof(header);
        
        assert(reinterpret_cast<long>(mBuffer.data()) % alignof(Header) == 0);
        assert(mCumulativeHeaderSize % alignof(Header) == 0);
        
        return *result;
    }
    
    void receive(Packet packet)
    {
        mReceiveFunction(*this, packet);
    }
    
private:    

    // Enum doesn't work well with bitmasks, so we use a typedef to int instead.    
    typedef int CommonProtocols;
    enum
    {
        IPv4 = 1 << 0,
        IPv6 = 1 << 1,
        TCP  = 1 << 2,
        UDP  = 1 << 3
    };
    
    
    
    void update_receive_function()
    {
        switch (mCommonProtocols)
        {
            case 0: mReceiveFunction = nullptr; break;
            
            case IPv4    : mReceiveFunction = &static_receive<IPv4>    ; break;
            case IPv4|UDP: mReceiveFunction = &static_receive<IPv4|UDP>; break;
            case IPv4|TCP: mReceiveFunction = &static_receive<IPv4|TCP>; break;
            
            case IPv6    : mReceiveFunction = &static_receive<IPv6>    ; break;
            case IPv6|UDP: mReceiveFunction = &static_receive<IPv6|UDP>; break;
            case IPv6|TCP: mReceiveFunction = &static_receive<IPv6|TCP>; break;
        }
    }
    
    template<CommonProtocols common_protocols>
    static bool static_receive(Stack& stack, Packet packet)
    {
        enum
        {
            has_ip4 = common_protocols & IPv4,
            has_ip6 = common_protocols & IPv6
        };
        
        if (has_ip4)
        {
            return stack.receive_impl<common_protocols>(*stack.mIPv4Header, packet);
        }
        else if (has_ip6)
        {
            return stack.receive_impl<common_protocols>(*stack.mIPv6Header, packet);
        }
        else
        {
            return false;
        }
    }
    
    template<CommonProtocols common_protocols>
    bool receive_impl(IPv4Header&, Packet packet)
    {
        enum
        {
            has_tcp = common_protocols & TCP,
            has_udp = common_protocols & UDP
        };
        
        if (packet.getEtherType() != EtherType::IPv4)
        {        
            switch (packet.getProtocol())
            {
                case IPProtNum::TCP:
                {
                    if (!has_tcp) return false;
                    return TCPProtocol::receive(*this, packet);
                }
                case IPProtNum::UDP:
                {
                    if (!has_udp) return false;
                    return UDPProtocol::receive(*this, packet);
                }
                case IPProtNum::ICMP:
                {
                    return ICMPProtocol::receive(*this, packet);
                }
                default:
                {
                    return false;
                }
            }
        }
        else if (packet.getEtherType() == EtherType::ARP)
        {
            // handle arp...
            return true;
        }
        else
        {
            return false;
        }
    }
    
    template<CommonProtocols common_protocols>
    bool receive_impl(IPv6Header&, Packet packet)
    {
        // ...
        return false;
    }
        
    struct FixAlignment
    {
        uint16_t mNothing;
    };
        
    using FPtr = decltype(&static_receive<0>);
    FPtr mReceiveFunction;    
    std::vector<uint8_t> mBuffer;    
    std::size_t mCumulativeHeaderSize = 0;
    EthernetHeader* mEthernetHeader = nullptr;
    IPv4Header* mIPv4Header = nullptr;
    IPv6Header* mIPv6Header = nullptr;
    CommonProtocols mCommonProtocols;
    
};


struct VLANHeader
{
    uint16_t a, b;
};


int main()
{
    Stack stack(1500);
    stack.addHeader(VLANHeader());
    stack.set_ip4();
}

