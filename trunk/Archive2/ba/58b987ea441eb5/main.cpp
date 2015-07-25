#include <boost/lockfree/spsc_queue.hpp>
#include <cstring>
#include <iostream>
#include <vector>


namespace Stack
{
    struct Internal {};
    
    struct Packet
    {
        const uint8_t* data() const;
        std::size_t size() const;
    };
}


struct Tx
{
    struct HigherLayer
    {        
        virtual void on_receive_buffers(Tx&, void** buffers, std::size_t* buffer_sizes, int num_buffers);        
    };
    
    void request_buffer(HigherLayer& higher_layer, uint16_t requested_buffer_size)
    {
        // ...?
    }
    
private:
    struct BufferRequest // ??
    {
        HigherLayer* mHigherLayer;
        int length;
    };
    
    struct BufferRequestQueue {};
    
    BufferRequestQueue mBufferRequests;
};
 


struct BBPort : Tx::HigherLayer
{
    BBPort() : mPackets(100)
    {        
    }
    
    // this call is protocolstack's L1 push method
    void sendPackets(Stack::Internal, const std::vector<Stack::Packet>& packets)
    {
        // Since the Tx is sometimes very busy we should not boldly push all our packets into it.
        // We should communicate our intention to send data and allow Tx to come
        // back to us when it is ready to process our data.
        
        // This method needs to be async/non-blocking so the protocol stack doesn't waste time here.
        
        // store packets in local member variable
        mPackets.push(packets.data(), packets.size()); // bulk push rather than packet-per-packet
        
        // request buffers from Tx for each of our packets
        // (a request_multiple_buffers call could also be useful here)
        for (auto& packet : packets)
        {
            tx.request_buffer(*this, packet.size()); // non-blocking!
        }
    }
    
    // Tx invokes this callback when it has obtained (some of the) requested buffers and is ready to receive the data from us.
    void on_receive_buffers(Tx&, void** buffers, std::size_t* lengths, int num_buffers) override final
    {
        // Process per 4 to reduce contention on the lock-free queue
        while (num_buffers > 4)
        {
            
            Stack::Packet packet[4];
            auto num_popped = mPackets.pop(&packet[0], 4); // bulk pop rather than packet-per-packet
            assert(num_popped == 4);
            
            // check if packet sizes match provided buffer lengths
            assert(lengths[0] == packet[0].size() 
                && lengths[1] == packet[1].size() 
                && lengths[2] == packet[2].size() 
                && lengths[3] == packet[3].size());
            
            memcpy(buffers[0], packet[0].data(), packet[0].size());
            memcpy(buffers[1], packet[1].data(), packet[1].size());
            memcpy(buffers[2], packet[2].data(), packet[2].size());
            memcpy(buffers[3], packet[3].data(), packet[3].size());
            
            num_buffers -= 4;
            buffers += 4;
            lengths += 4;
        }
        
        while (num_buffers > 0)
        {
            Stack::Packet packet;
            mPackets.pop(packet);
            memcpy(*buffers, packet.data(), packet.size());
            num_buffers--;
            lengths++;
            buffers++;
        }
    }
    
    Tx tx;
    boost::lockfree::spsc_queue<Stack::Packet> mPackets;
};



int main()
{
}
