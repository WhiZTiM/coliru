#ifndef STACK_IPV4PROTOCOL_H
#define STACK_IPV4PROTOCOL_H


#include "Stack/IPv4Header.h"
#include "Stack/EthernetHeader.h"
#include "Stack/Initialized.h"
#include "Stack/Internal.h"
#include "Stack/VLANHeader.h"
#include "IPv4Address.h"
#include "MACAddress.h"


namespace Stack {


struct EthernetDecoder;
struct EthernetProtocol;
struct IPv4Protocol;
struct IPv6Protocol;
struct UDPProtocol;
struct TCPProtocol;
class ProtocolStack;


struct EthernetProtocol
{
    void registerIPv4(Internal, IPv4Protocol& inIPv4Protocol);
    void registerIPv6(Internal, IPv6Protocol& inIPv6Protocol);

    void pop(Internal in, ReceivedData data);
    void push(Internal in, Packet& packet);

    void setLocalMAC(Internal, LocalMAC inLocalMAC) { mLocalMAC = inLocalMAC; }

private:
    void handleARP(const EthernetDecoder& dec);

    LocalMAC mLocalMAC;
    IPv4Protocol* mIPv4Protocol = nullptr;
    IPv6Protocol* mIPv6Protocol = nullptr;
    boost::optional<VLANHeader> mVLANHeader;
};


struct IPv4Protocol
{
    void pop(Internal in, ReceivedData data);
    void push(Internal in, Packet& packet);

private:
    virtual void do_push(Internal in, Packet& packet) = 0;

    LocalIPv4 mLocalIP{};
    IPv4Address mNetMask{};
    IPv4Address mGateway{};
    TCPProtocol* mTCPProtocol = nullptr;
    UDPProtocol* mUDPProtocol = nullptr;
};


struct IPv4Protocol_Over_Ethernet : IPv4Protocol
{
    IPv4Protocol_Over_Ethernet(Internal in, EthernetProtocol& inEthernetProtocol);

private:
    void do_push(Internal in, Packet& packet) final;

    EthernetProtocol* mEthernetProtocol = nullptr;
};


struct TCPv4Connection
{
    TCPv4Connection(TCPProtocol& inTCPProtocol);

    void pop(Internal in, const TCPDecoder& tcpdec, const IPv4Decoder& ipdec);
    void push(Internal in, Packet& packet);

private:
    TCPProtocol* mTCPProtocol = nullptr;
};


struct TCPProtocol
{
    using SessionKey = std::tuple<LocalIP, RemoteIP, LocalPort, RemotePort>;

    TCPProtocol(IPv4Protocol& inIPv4Protocol);

    void pop(Internal in, const IPv4Decoder& ipdec);

    void push(Internal in, Packet& packet)
    {
        mIPv4Protocol->push(in, packet);
    }

private:
    IPv4Protocol* mIPv4Protocol;
    boost::container::flat_map<SessionKey, boost::optional<TCPv4Connection>> mConnections;
};


} // namespace Stack


#endif // STACK_IPV4PROTOCOL_H
