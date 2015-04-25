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
    template<typename T>
    Processor(T) : mImpl(new BabyImpl<T>())
    {
    }
    
    void process(const Packet& packet)
    {
        mImpl->process(*this, packet);
    }
    
    
private:
    struct Base
    {   
        virtual ~Base() {}
        virtual void process(Processor&, const Packet&) = 0;
    };
    
    template<typename ProcessorType>
    struct Impl : Base
    {
        
        Impl(const Packet& first_packet) :
            mSnapshot(ProcessorType::CreateSnapshot(first_packet, mConfig))
        {
        }
        
        void process(Processor&, const Packet& packet)
        {
            ProcessorType::process(packet, mConfig, mSnapshot);
        }
        
        using Snapshot = typename ProcessorType::Snapshot;
        using Config   = typename ProcessorType::Config;
        
        
        Config mConfig;
        Snapshot mSnapshot;
    };
    
    template<typename T>
    struct BabyImpl : Base
    {
        void process(Processor& processor, const Packet& first_packet)
        {
            processor.mImpl.reset(new Impl<T>(first_packet));
        }
    };
    
    std::unique_ptr<Base> mImpl;
};


struct SizeCounter
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
    
    struct Config {};
    
    static Snapshot CreateSnapshot(const Packet& packet, const Config&)
    {
        return Snapshot(packet);
    }
    
    static void process(const Packet& packet, const Config&, Snapshot& snapshot)
    {
        snapshot.update(packet);
        
    }
};


struct LatencyCounter
{
    struct Snapshot
    {   
        Snapshot(std::int64_t latency)
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
    
    static Snapshot CreateSnapshot(const Packet& packet, const Config& config)
    {
        return Snapshot(config.getLatency(packet));
    }
    
    static void process(const Packet& packet, const Config& config, Snapshot& snapshot)
    {
        snapshot.update(config.getLatency(packet));
        
    }
};


int main()
{
    Processor sizecounter(SizeCounter{});
    Processor latency_counter(LatencyCounter{});
    
    sizecounter.process(Packet("1"));
    latency_counter.process(Packet("1"));
    sizecounter.process(Packet("1"));
    sizecounter.process(Packet("1"));
    latency_counter.process(Packet("1"));
    latency_counter.process(Packet("1"));
    
    sizecounter.process(Packet("1"));
    sizecounter.process(Packet("1"));
    sizecounter.process(Packet("1"));
    latency_counter.process(Packet("1"));
    latency_counter.process(Packet("1"));
    latency_counter.process(Packet("1"));
}


