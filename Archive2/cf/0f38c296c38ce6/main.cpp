#include <cstddef>
#include <type_traits>


namespace Stack2 {


struct ReceivedData
{
};


struct Packet
{
};


struct IPv4Protocol;
struct TCPProtocol;
struct Ethernet;



struct Stack
{
    template<class HLP, class LLP, class HLPIdentifier>
    HLP& acquireProtocol(LLP& inLLP, HLPIdentifier inHLPIdentifier)
    {
        auto old_offset = mProtocolStorageOffset;
        auto alloc_size = align(sizeof(HLP));

        mProtocolStorageOffset += alloc_size;

        void* storage = static_cast<char*>(static_cast<void*>(&mProtocolStorage)) + old_offset;

        HLP& result = *new (storage) HLP(*this, inLLP, inHLPIdentifier);
        inLLP.addHLP(result);
        return result;
    }

    static std::size_t align(std::size_t n)
    {
        return (n + 127) & ~127;
    }

    using ProtocolStorage = std::aligned_storage<10000, 128>::type;

    ProtocolStorage mProtocolStorage;
    std::size_t mProtocolStorageOffset = 0;
};


struct LinkLayer
{
    void push(Packet& packet)
    {
        (void)packet;
    }

private:
    virtual void do_push(Packet&) = 0;
};






struct Ethernet : LinkLayer
{
    Ethernet(Stack&) { }

    void pop(ReceivedData data)
    {
        EthernetDecoder dec(data);
        if (dec.getEtherType() == EtherType::IPv4)
        {
            if (mIPv4Protocol)
            {
                mIPv4Protocol->pop(GetPayload(dec));
            }
        }
    }

    void addHLP(IPv4Protocol& inIPv4Protocol)
    {
        mIPv4Protocol = &inIPv4Protocol;
    }

    IPv4Protocol* mIPv4Protocol;
};


struct IPv4Protocol
{
    IPv4Protocol(Stack&, Ethernet& inEthernet) :
        mEthernet(&inEthernet),
        mTCPProtocol()
    {
    }

    void pop(ReceivedData data)
    {
        IPv4Decoder dec(data);
        if (dec.getProtocol() == IPProtNum::TCP)
        {
            if (mTCPProtocol)
            {
                mTCPProtocol->pop(dec);
            }
        }
    }

    void push(Packet& packet)
    {
        mEthernet->push(packet);
    }

    void addHLP(TCPProtocol& inTCPProtocol)
    {
        mTCPProtocol = &inTCPProtocol;
    }

    Ethernet* mEthernet = nullptr;
    TCPProtocol* mTCPProtocol = nullptr;
};


struct SocketBuffer
{
    SocketBuffer(TCPDecoder tcpdec, IPv4Decoder ipdec) :
        mStorage(tcpdec.packet_begin(), tcpdec.end()),
        mTCP(reinterpret_cast<TCPHeader*>(mStorage.data() + tcpdec.offset())),
        mIPv4(reinterpret_cast<IPv4Header*>(mStorage.data() + ipdec.offset())),
        mEth(reinterpret_cast<EthernetHeader*>(mStorage.data())),
        mTCPLength(tcpdec.getHeaderLength()),
        mIPLength(ipdec.getHeaderLength()),
        mL2Length(ipdec.offset())
    {
        std::swap(mTCP->SourcePort, mTCP->DestinationPort);
        std::swap(mIPv4->SourceAddress, mIPv4->DestinationAddress);
    }

    const std::uint8_t* begin() const { return mStorage.data(); }

    const std::uint8_t* ip_begin() const { return mStorage.data() + mL2Length; }
    const std::uint8_t* ip_end()   const { return ip_begin() + mIPLength; }

    const std::uint8_t* tcp_begin() const { return ip_end(); }
    const std::uint8_t* tcp_end()   const { return tcp_begin() + mTCPLength; }

    const std::uint8_t* l5_begin() const { return tcp_end(); }
    const std::uint8_t* l5_end() const { return mStorage.end(); }

    // contains the packet storage
    DynamicBuffer mStorage;

    TCPHeader* mTCP;
    IPv4Header* mIPv4;
    EthernetHeader* mEth;
    short mTCPLength;
    short mIPLength;
    short mL2Length;
};


struct TCPSession
{
    TCPSession(IPv4Protocol& inIP, TCPDecoder tcpdec, IPv4Decoder ipdec) :
        mIPv4Protocol(&inIP),
        mSocketBuffer(1, SocketBuffer(tcpdec, ipdec))
    {
    }

    void send(const std::string& s)
    {
        SocketBuffer& buf = mSocketBuffer.back();
        mSocketBuffer.pop_back();

        Packet packet(buf.begin(), buf.l5_begin() + s.size());
        memcpy(packet.data() - s.size(), s.data(), s.size());

        mIPv4Protocol->push(packet);
    }

    IPv4Protocol* mIPv4Protocol;
    std::vector<SocketBuffer> mSocketBuffer;
};


struct TCPProtocol
{
    TCPProtocol(Stack& inStack, IPv4Protocol& inIPv4Protocol) :
        mStack(&inStack),
        mIPv4Protocol(&inIPv4Protocol)
    {
    }

    void pop(IPv4Decoder ipdec)
    {
        TCPDecoder dec(ipdec);
        TCPSession& session = mMap[dec.getSourcePort()];
        session.send("test");
    }

    Stack* mStack;
    IPv4Protocol* mIPv4Protocol;
    boost::container::flat_map<RemotePort, TCPSession> mMap;
};


} // Stack2

