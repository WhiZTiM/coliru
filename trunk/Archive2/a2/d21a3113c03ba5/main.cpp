#include <algorithm>
#include <cstdint>
#include <cstring>
#include <memory>


struct Packet
{
    std::uint8_t* GetData() { return nullptr; }
    std::uint32_t GetSize() { return 0; }
};


struct PacketGroup
{
};


struct Processor
{
    template<typename Derived>
    Processor(Derived&) : mImpl(new BabyImpl<Derived>())
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
    
    template<typename Derived>
    struct Impl : Base
    {
        using Snapshot = typename Derived::Snapshot;
        
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
    
    template<typename Derived>
    struct BabyImpl
    {
        void process(Processor& processor, const Packet& first_packet)
        {
            processor.mImpl.reset(new Impl<Derived>(first_packet));
        }
    };
    
    std::unique_ptr<Base> mImpl;
};


struct SizeCounter : Processor
{
    struct Snapshot
    {   
        explicit Snapshot(std::int32_t initial_size) :
        {   
            mMinimum = initial_size;
            mMaximum = initial_size;
            mBytes = initial_size;
            mFrames = 1;
        }
        
        void update(std::int32_t size)
        {
            mMinimum = std::min(mMinimum, size);
            mMaximum = std::max(mMaximum, size);
            mBytes += size;
            mFrames++;
        }
        
        std::int32_t mMinimum;
        std::int32_t mMaximum;
        std::int64_t mBytes;
        std::int64_t mFrames;
    };
    
    SizeCounter() : Processor(this)
    {
    }
    
    void do_process(const Packet& packet)
    {
        mSnapshot.update(packet.size());
    }
    
    void do_process(const PacketGroup& group)
    {
        mSnapshot.mMinimum = group.minimumSize();
        mSnapshot.mMaximum = group.maximumSize();
        mSnapshot.mBytes = group.mBytes();
        mSnapshot.mFrames = group.size();
    }
    
    Snapshot mSnapshot;
};

