#include "Config.h"
#include "Stack/IPv4Protocol.h"
#include "Stack/IPv4Decoder.h"
#include "Stack/ARPDecoder.h"
#include "Stack/TCPProtocol.h"
#include "Stack/VLANDecoder.h"
#include "Stack/EthernetProtocol.h"
#include "Stack/ProtocolStack.h"


namespace Stack {


void EthernetProtocol::registerIPv4(Internal, IPv4Protocol& inIPv4Protocol)
{
    mIPv4Protocol = &inIPv4Protocol;
}


void EthernetProtocol::registerIPv6(Internal, IPv6Protocol& inIPv6Protocol)
{
    mIPv6Protocol = &inIPv6Protocol;
}


void EthernetProtocol::push(Internal in, Packet& packet)
{
    // TODO: Implement
    (void)in;
    (void)packet;
}


void EthernetProtocol::handleARP(const EthernetDecoder& dec)
{
    // TODO: Implement
    ARPDecoder arpdec(dec);
    (void)arpdec;
}


void EthernetProtocol::pop(Internal in, ReceivedData data)
{
    EthernetDecoder dec(data);
    if (!dec.validate())
    {
        return;
    }

    if (dec.getDestinationMAC() != mLocalMAC && !dec.getDestinationMAC().isMulticast())
    {
        return;
    }

    switch (dec.getEtherType())
    {
        case EtherType::IPv4:
        {
            if (mIPv4Protocol) mIPv4Protocol->pop(in, dec.getPayload());
            return;
        }
        case  EtherType::IPv6:
        {
            if (mIPv6Protocol) mIPv6Protocol->pop(in, dec.getPayload());
            return;
        }
        case EtherType::VLAN:
        {
            throw std::runtime_error("TODO: Fix VLAN");
        }
        case EtherType::ARP:
        {
            handleARP(dec);
            return;
        }
        // no default case. compiler warning will be triggered unless all cases are implemented.
    }
}


void IPv4Protocol::pop(Internal in, ReceivedData data)
{
    IPv4Decoder ipdec(data);

    if (!ipdec.validate())
    {
        return;
    }

    switch (ipdec.getProtocol())
    {
        case IPProtNum::TCP:
        {
            if (mTCPProtocol)
            {
                mTCPProtocol->pop(in, ipdec);
            }
            break;
        }
        case IPProtNum::UDP:
        {
            if (mUDPProtocol)
            {
                mUDPProtocol->pop(in, ipdec);
            }
            break;
        }
        // TODO
    }
}


void IPv4Protocol::push(Internal in, Packet& packet)
{
    do_push(in, packet);
}


IPv4Protocol_Over_Ethernet::IPv4Protocol_Over_Ethernet(Internal in, EthernetProtocol& inEthernetProtocol) :
    IPv4Protocol(),
    mEthernetProtocol(&inEthernetProtocol)
{
    mEthernetProtocol->registerIPv4(in, *this);
}


void IPv4Protocol_Over_Ethernet::do_push(Internal in, Packet& packet)
{
    mEthernetProtocol->push(in, packet);
}


TCPProtocol::TCPProtocol(IPv4Protocol& inIPv4Protocol) :
    mIPv4Protocol(&inIPv4Protocol)
{
}


void TCPProtocol::pop(Internal in, const IPv4Decoder& ipdec)
{
    TCPDecoder tcpdec(ipdec);

    if (!tcpdec.validate())
    {
        return;
    }

    SessionKey key(tcpdec.getSourcePort(), ipdec.getSource(), tcpdec.getDestinationPort(), ipdec.getDestination());

    auto connection = mConnections[key];
    if (!connection)
    {
        connection = TCPv4Connection();
    }

    TCPv4Connection& conn = *connection;
    conn.pop(tcpdec, ipdec);

}


void TCPv4Connection::pop(const TCPDecoder& tcpdec, const IPv4Decoder& ipdec)
{
    Packet packet;
    push(packet);
}


TCPv4Connection::TCPv4Connection(TCPProtocol& inTCPProtocol) :
    mTCPProtocol(&inTCPProtocol)
{
}

void TCPv4Connection::push(Internal in, Packet& packet)
{
    packet.push_front(TCPHeader());
    packet.push_front(IPv4Header());
}



} // namespace Stack
