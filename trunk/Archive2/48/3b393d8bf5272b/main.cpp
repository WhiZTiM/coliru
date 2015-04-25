#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>


struct Packet
{
    Packet(const char* payload) : payload_(payload) {}
    
    const char* data() const { return payload_.c_str(); }
    std::int32_t size() const { return payload_.size(); }
    
    std::int64_t getTimestamp() const
    {
        static std::int64_t dummy;
        return dummy = 10 + rand() % 20;
    }
    
    std::string payload_;
};


struct PacketGroup
{
};





struct Processor
{
    struct Impl
    {
        virtual ~Impl() {}
        virtual void process(const Packet& packet) = 0;
    };

    Processor(Impl* inImpl) : mImpl(inImpl) {}
    
    void process(const Packet& packet)
    {
        mImpl->process(packet);
    }
    
private:
    std::unique_ptr<Impl> mImpl;
};


struct SizeCounter : Processor::Impl
{
    struct Snapshot
    {   
        explicit Snapshot(const Packet& packet)
        {   
            mMinimum = packet.size();
            mMaximum = packet.size();
            mBytes = packet.size();
            mFrames = 1;
            std::cout << "*** SizeCounter: mFrames=" << mFrames << " mBytes=" << mBytes << std::endl;
        }
        
        void update(const Packet& packet)
        {
            mMinimum = std::min(mMinimum, packet.size());
            mMaximum = std::max(mMaximum, packet.size());
            mBytes += packet.size();
            mFrames++;
            
            std::cout << "SizeCounter: mFrames=" << mFrames << " mBytes=" << mBytes << std::endl;
        }

        std::int32_t mMinimum;
        std::int32_t mMaximum;
        std::int64_t mBytes;
        std::int64_t mFrames;
    };
    
    SizeCounter()
    {
    }
    
    void process(const Packet& packet)
    {
        if (!mSnapshot)
        {
            mSnapshot.reset(new Snapshot(packet));
            return;
        }
        mSnapshot->update(packet);
    }
    
    std::unique_ptr<Snapshot> mSnapshot;
};


struct LatencyCounter :  Processor::Impl
{
    struct Snapshot
    {   
        explicit Snapshot(std::int64_t latency)
        {
            mMinimum = latency;
            mMaximum = latency;
            mTotal = latency;
            mCounter = 1;
            std::cout << "*** LatencyCounter: mMinimum=" << mMinimum << " mMaximum=" << mMaximum << std::endl;
        }
        
        void update(std::int64_t latency)
        {
            mMinimum = std::min(mMinimum, latency);
            mMaximum = std::max(mMaximum, latency);
            mTotal += latency;
            mCounter++;
            
            std::cout << "LatencyCounter: mMinimum=" << mMinimum << " mMaximum=" << mMaximum << std::endl;
        }
        
        double average() const
        {
            return 1.0 * mTotal / mCounter;;
        }
        
        std::int64_t mMinimum;
        std::int64_t mMaximum;
        std::int64_t mTotal;
        std::int64_t mCounter;
    };
    
    struct Config
    {
        void setTagOffset(std::int32_t offset)
        {
            mOffset = offset;
        }
        
        template<typename Packet>
        std::int64_t getLatency(const Packet& packet) const
        {
            std::int64_t result;
            std::memcpy(&result, packet.data() + (packet.size() - mOffset), sizeof(result));
            return packet.getTimestamp() - result;
        }
        
        std::int32_t mOffset = 0;
    };
    
    void process(const Packet& packet)
    {
        if (!mSnapshot)
        {
            mConfig.reset(new Config);
            mSnapshot.reset(new Snapshot(mConfig->getLatency(packet)));
            return;
        }
        mSnapshot->update(mConfig->getLatency(packet));
    }
    
    std::unique_ptr<Snapshot> mSnapshot;
    std::unique_ptr<Config> mConfig;
};


int main()
{
    Processor sizecounters(new SizeCounter);
    Processor latencycount(new LatencyCounter);
    
    sizecounters.process(Packet("1"));
    latencycount.process(Packet("1"));
    
    sizecounters.process(Packet("1"));
    sizecounters.process(Packet("1"));    
    sizecounters.process(Packet("1"));
    sizecounters.process(Packet("1"));
    
    latencycount.process(Packet("1"));
    latencycount.process(Packet("1"));
    latencycount.process(Packet("1"));
    latencycount.process(Packet("1"));
}


