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
        struct Pool
        {
            Impl* pop()
            {
                if (mStorage.empty())
                {
                    return new Impl;
                }
                
                auto result = mStorage.back();
                mStorage.pop_back();
                return result;                
            }
            
            void push(Impl* impl)
            {
                mStorage.push_back(impl);
            }
            
            std::size_t size() const { return mStorage.size(); }
            
            std::vector<Impl*> mStorage;
        };
        
        static Pool& GetPool()
        {
            static Pool fPool;
            return fPool;
        }
        
        static Impl* Allocate()
        {
            return GetPool().pop();
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
            GetPool().push(this);
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
    Packet p12;
    {
        Packet p21;
        Packet p22;
        {
            Packet p31;
            Packet p32;
        }
        Packet p23;
        Packet p24;
    }
    Packet p13;
    Packet p14;
}
