#include <boost/lockfree/stack.hpp>
#include <iostream>
#include <vector>
#include <mutex>
#include <sstream>
#include <thread>


struct LogItem
{
    ~LogItem()
    {
        static std::mutex m;
        std::lock_guard<std::mutex> l(m);
        std::cout << ss.str() << std::endl;
    }

    std::ostringstream ss;
};
#define LOG() if (0) ; else LogItem().ss

    static long sane_thread_id()
    {
        static std::atomic<long> counter{0};
        static __thread const long id = counter++;
        return id;
    }
    

template<typename T>
struct Pool
{
    

    T* allocate()
    {
        auto poolIndex = sane_thread_id() % num_pools;
        auto block = mLocalPools[poolIndex].allocate();
        //LOG() << "Block::Block  : block=" << block << " pool=" << poolIndex << " threadid=" << sane_thread_id();
        return block->data();
    }

    void deallocate(T* t)
    {
        auto block = reinterpret_cast<typename LocalPool::Block*>(reinterpret_cast<LocalPool**>(t) - 1);
        block->release();
    }

    struct LocalPool
    {
        enum { Capacity = 100 };

        struct Storage
        {
            T* data()
            {
                return static_cast<T*>(static_cast<void*>(&mStorage));
            }
    
            typename std::aligned_storage<sizeof(T), alignof(T)>::type mStorage;
        };
    
        struct Block
        {
            explicit Block(LocalPool* inLocalPool) :
                mLocalPool(inLocalPool)
            {
            }
    
            T* data()
            {
                return mStorage.data();
            }
    
            void release()
            {
                //LOG() << "Block::release: block=" << this << " pool=" << mLocalPool;
                if (mLocalPool)
                {
                    mLocalPool->deallocate(this);
                }
                else
                {
                LOG() << "FREEING BLOCK";
                    free(this);
                }
            }
    
            LocalPool* mLocalPool;
            Storage mStorage;
        };
    
        LocalPool()
        {
            for (int i = 0; i != Capacity; ++i)
            {
                auto block = mallocate();
                block->mLocalPool = this;
                mStack.push(block);
            }
        }


        ~LocalPool()
        {
            Block* block;
            auto counter = 0;
            while (mStack.pop(block))
            {
                counter++;
                free(block);
            }
            LOG() << "Freed " << counter << '/' << Capacity;
        }
        
        Block* allocate() 
        {
            Block* result;
            if (mStack.pop(result))
            {
                return new (result) Block(this);
            }
            LOG() << "MALLOCATE";
            return mallocate();
        }
        
        Block* mallocate()
        {
            return new (malloc(sizeof(Block))) Block(nullptr);
        }
    
        void deallocate(Block* block)
        {
            assert(block->mLocalPool == this);
            if (!mStack.push(block))
            {
                free(block);
            }
        }
    
        boost::lockfree::stack<Block*, boost::lockfree::capacity<Capacity>> mStack;
    };
    
    enum { num_pools = 32 };
    LocalPool mLocalPools[num_pools];
};




int main()
{
    Pool<int> pool;
    auto task = [&pool]{
        std::vector<int*> allocs;
        allocs.reserve(100);
        for (int i = 0; i != 102; ++i) {
            allocs.push_back(new (pool.allocate()) int(i));
        }
        //std::random_shuffle(allocs.begin(), allocs.end());
        for (auto& ptr : allocs) {
            pool.deallocate(ptr);
        }
        std::stringstream ss;
        ss << sane_thread_id() << ":";
        allocs.clear();
        for (int i = 0; i != 100; ++i) {
            auto& n = *((int*)pool.allocate());
            ss << n << ' ';
            allocs.push_back(&n);
        }
        for (auto& alloc : allocs) {
            pool.deallocate(alloc);
        }
        LOG() << ss.str();
    };

    std::thread t1(task), t2(task), t3(task);
    t1.join(), t2.join(), t3.join();
}
