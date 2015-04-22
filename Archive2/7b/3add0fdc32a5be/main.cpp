#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <sstream>
#include <vector>
#include <thread>
        
long sane_thread_id()
{
    static std::atomic<long> counter{0};
    static __thread const long id = counter++;
    return id;
}
        
std::mutex m;

struct LogItem
{
    std::stringstream ss;
    
    ~LogItem()
    {
        std::lock_guard<std::mutex> lock(m);
        std::cout << ss.str() << std::endl;
    }
};


#define LOG() if (false) ; else LogItem().ss


struct FreeListPool
{
    void* allocate(std::size_t n)
    {
        auto result = malloc(n);
        return result;
    }
    
    void deallocate(void* ptr, std::size_t n)
    {
        free(ptr);
        (void)n;
    }
};

std::atomic<uint32_t> contentions;
std::atomic<uint32_t> locks;

struct Pool
{
    enum { num_pools = 64 };
    
    Pool() :
        mMutices(),
        mFreeListPools(num_pools)
    {
    }
    
    void* allocate(std::size_t n)
    {
        n = align(n);
        
        // choose a somewhat random pool index
        auto pool_index = (n + mAllocs++) % num_pools;
    	//LOG() << "allocate " << n << " pool_index=" << pool_index;
        
        auto& mtx = mMutices[pool_index];
        if (!mtx.try_lock())
        {
            contentions++;
            mtx.lock();
        }
        locks++;
        std::lock_guard<std::mutex> lock(mMutices[pool_index], std::adopt_lock);
        
        std::uint64_t* memory = static_cast<std::uint64_t*>(mFreeListPools[pool_index].allocate(n + sizeof(std::uint64_t)));
        memory[0] = pool_index; 
        return memory + 1;
    }
    
    void deallocate(void* ptr, std::size_t n)
    {
        n = align(n);

        std::uint64_t* memory = static_cast<std::uint64_t*>(ptr) - 1;
        
        auto pool_index = memory[0];

		//LOG() << "deallocate " << n << " pool_index=" << pool_index;
        
        
        std::lock_guard<std::mutex> lock(mMutices[pool_index]);
        mFreeListPools[pool_index].deallocate(memory, n);
    }

    std::size_t align(std::size_t n)
    {
        auto r = n % 8;
        return n + bool(r) * (8 - r);
    }
    
    std::mutex mMutices[num_pools];
    std::vector<FreeListPool> mFreeListPools;
    std::atomic<std::uint32_t> mAllocs{0};
};


std::atomic<int> started{0};




enum { num_threads = 10 };

Pool pool;

void test()
{
    started++;
    while (started != num_threads);
    for (int i = 0; i != 1000; ++i)
    {
        pool.deallocate(pool.allocate(1 + i), 1 + i);
    }
}


int main()
{
	struct Thread : std::thread
	{
		Thread() : std::thread([]{ test(); }) {}
		~Thread() { join(); }
	};

	{ Thread threads[num_threads]; }

    std::cout << "contentions=" << contentions << " locks=" << locks << std::endl;
}

