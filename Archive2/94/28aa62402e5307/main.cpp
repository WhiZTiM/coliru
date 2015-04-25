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
    
    template<typename T>
    struct Impl : Base
    {
        using Snapshot = typename T::Snapshot;
        
        Impl(const Packet& first_packet) :
            mSnapshot(first_packet)
        {
        }
        
        void process(Processor&, const Packet& packet)
        {
            mSnapshot.update(packet);
        }
        
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
            std::cout << "Snapshot::Snapshot: mFrames=" << mFrames << " mBytes=" << mBytes << std::endl;
        }
        
        void update(const Packet& packet)
        {
            mMinimum = std::min(mMinimum, packet.size());
            mMaximum = std::max(mMaximum, packet.size());
            mBytes += packet.size();
            mFrames++;
            
            std::cout << "Snapshot::update:   mFrames=" << mFrames << " mBytes=" << mBytes << std::endl;
        }

        std::int32_t mMinimum;
        std::int32_t mMaximum;
        std::int64_t mBytes;
        std::int64_t mFrames;
    };
};


int main()
{
    Processor processor(SizeCounter{});
    
    processor.process(Packet("1"));
    processor.process(Packet("1"));
    processor.process(Packet("1"));
    processor.process(Packet("1"));
    processor.process(Packet("1"));
}


