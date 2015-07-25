


struct Tx
{
    // Tx users can implement this
    struct HigherLayer
    {   
        virtual void on_receive_buffer(Tx&, void* buffers, int length) = 0;
    };
    
    void request_buffer(HigherLayer& higher_layer, uint16_t requested_buffer_size)
    {
        // tx stuff
    }
};
 


struct BBPort : Tx::HigherLayer
{    
    // this call orginates from the stack
    void sendPacket(Internal, const Packet& packet)
    {
        // packet is ref-counted, so this is a cheap copy
        pending_packets.push(packet);
        
        // tell the tx that we want to send data
        // tx will callback on_receive_buffer
        tx.request_buffer(*this, packet.size()); // non-blocking
    }
    
    // invoked by tx
    virtual void on_receive_buffer(Tx&, void* buffer, int length) override final
    {
        Packet packet;
        pending_packets.pop(packet);
        memcpy(buffer, packet.data(), packet.size());
    }
    
    Tx tx;
    ConcurrentQueue<Packet> pending_packets;
};
