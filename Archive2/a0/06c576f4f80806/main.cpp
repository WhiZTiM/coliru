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


template<typename Block, std::size_t Capacity_ = 1000>
struct LocalPool
{
    enum { Capacity = Capacity_ };

    LocalPool()
    {
    }

    Block* allocate() 
    {
        Block* result;
        if (mStack.pop(result))
        {
            return new (result) Block(this);
        }
        return new (malloc(sizeof(Block))) Block(this);

    }

    void deallocate(Block* block)
    {
        if (!mStack.push(block))
        {
            free(block);
        }
    }

    boost::lockfree::stack<Block*, boost::lockfree::capacity<Capacity>> mStack;
};


template<typename T>
struct Pool
{

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
        explicit Block(LocalPool<Block>* inLocalPool) :
            mLocalPool(inLocalPool)
        {
        }

        T* data()
        {
            return mStorage.data();
        }

        void release()
        {
            LOG() << "Block::release: block=" << this << " pool=" << mLocalPool;
            mLocalPool->deallocate(this);
        }

        LocalPool<Block>* mLocalPool;
        Storage mStorage;
    };

    T* allocate()
    {
        auto poolIndex = sane_thread_id() % num_pools;
        auto block = mLocalPools[poolIndex].allocate();
        LOG() << "Block::Block  : block=" << block << " pool=" << poolIndex << " threadid=" << sane_thread_id();
        return block->data();
    }

    void deallocate(T* t)
    {
        auto block = static_cast<Block*>(static_cast<void*>(static_cast<char*>(static_cast<void*>(t)) - sizeof(LocalPool<Block>*)));
        block->release();
    }

    static long sane_thread_id()
    {
        static std::atomic<long> counter{0};
        static __thread const long id = counter++;
        return id;
    }
    enum { num_pools = 32 };
    LocalPool<Block> mLocalPools[num_pools];
};



Pool<int> pool;

std::atomic<int> a;

int main()
{
    for (int i = 0; i != 8; ++i) {
        std::thread([]{
            a++;
            while (a != 0) {}
            std::vector<int*> allocs;
            allocs.reserve(100);
            for (int i = 0; i != 100; ++i) {
                allocs.push_back(new (pool.allocate()) int(i));
            }
            std::random_shuffle(allocs.begin(), allocs.end());
            for (auto& ptr : allocs) {
                pool.deallocate(ptr);
            }
            a++;
        }).detach();
    }
    
    
    while (a != 8) {}
    a = 0;
    while (a != 8) {}
}

