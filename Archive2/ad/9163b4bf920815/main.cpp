#include <atomic>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>


#define TRACE std::cout << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << std::endl;


struct Packet
{
    Packet() : mImpl(Impl::Allocate())
    {
    }
    
    Packet(const Packet& rhs) :
        mImpl(rhs.mImpl)
    {
        ++mImpl->mRefCount;
        
    }
    
    Packet& operator=(const Packet& rhs)
    {
        Packet(rhs).swap(*this);
        return *this;
    }
    
    ~Packet()
    {      
        mImpl->release();
    }
    
    void swap(Packet& rhs)
    {
        std::swap(mImpl, rhs.mImpl);
    }
    
    std::uint16_t use_count() const
    {
        return mImpl ? mImpl->mRefCount.load() : 0;
    }
    
    struct Impl
    {        
        using Pool = std::vector<Impl*>;
        
        static Pool& GetPool()
        {
            static Pool fPool;
            return fPool;
        }
        
        static Impl* Allocate()
        {
            auto& pool = GetPool();
            if (!pool.empty())
            {
                auto result = pool.back();
                pool.pop_back();
                std::cout << "Allocate: pool size is now " << pool.size() << std::endl;
                return result;
            }
            std::cout << "Allocate: return new Impl" << std::endl;
            return new Impl();
        }
        
        void release()
        {
            if (mRefCount == 1)
            {
                do_release();
            }
            else
            {
                --mRefCount;
            }
        }
        
        void do_release()
        {
            mData.clear();
            GetPool().push_back(this);
            std::cout << "do_release: pool size is now: " << GetPool().size() << std::endl;
        }
        
    private:
        Impl() : mRefCount(1), mData() {}
        
    public:
        std::atomic<std::uint16_t> mRefCount;
        char padding[128 - sizeof(mRefCount)];
        std::vector<char> mData;
    };
    
    Impl* mImpl;
};


int main()
{
    Packet p11;
    {
        Packet p21;
        Packet p22;
        {
            Packet p31;
            Packet p32;
            Packet p33;
            Packet p34;
        }
        Packet p23;
        Packet p24;
    }
}