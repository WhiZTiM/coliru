#include <array>
#include <set>
#include <vector>
#include <iostream>


struct Pool
{
    ~Pool()
    {
        for (auto ptr : mCleanup)
        {
            ::operator delete (ptr);
        }
    }
    
    void* allocate(std::size_t n)
    {
        auto aligned_n = nextpow2(align(n));        
        //std::cout << "allocate: " << n << " => " << aligned_n << std::endl;
        auto pool_index = get_pool_index(aligned_n);
        return do_allocate(aligned_n, pool_index);
    }
    
    void deallocate(void* ptr, std::size_t n)
    {
        auto aligned_n = nextpow2(align(n));
        //std::cout << "deallocate: " << n << " => " << aligned_n << std::endl;
        auto pool_index = get_pool_index(aligned_n);
        return do_deallocate(ptr, aligned_n, pool_index);
    }
    
    void print()
    {
        for (auto& pool : pools)
        {
            std::cout << ' ' << pool.size();
        }
        std::cout << std::endl;
    }

private:
    void* do_allocate(std::size_t n, std::size_t pool_index)
    {
        if (pool_index < num_pools)
        {
            auto& pool = pools[pool_index];
            if (!pool.empty())
            {
                auto result = pool.back();
                pool.pop_back();
                return result;
            }
    
            auto result = static_cast<char*>(do_allocate(n * 2, pool_index + 1));
            pool.push_back(result + n);
            return result;
        }
        else
        {        
            auto result = ::operator new(n);
            mCleanup.insert(result);
            return result;
        }
    }

    void do_deallocate(void* ptr, std::size_t n, std::size_t pool_index)
    {
        if (pool_index < num_pools)
        {
            auto& pool = pools[pool_index];
            pool.push_back(ptr);
        }
        
        ::operator delete(ptr);
        mCleanup.erase(ptr);
    }

    enum
    {
        alignment = 16,
        num_pools = 8
    };

    int log2(int x)
    {
        int y;
        asm( "\tbsr %1, %0\n"
            : "=r"(y)
            : "r" (x));
        return y;
    }

    int nextpow2(int x)
    {
        --x;
        x |= x >> 1;
        x |= x >> 2;
        x |= x >> 4;
        x |= x >> 8;
        x |= x >> 16;
        return x+1;
    }
    
    std::size_t align(std::size_t n)
    {
        return (n + alignment - 1) & ~(alignment - 1);
    }
    
    std::size_t get_pool_index(std::size_t n)
    {
        return n <= 16 ? 0 : (log2(n) - 4);
    }
    
    struct BlockList : std::vector<void*>
    {
        BlockList()
        {
            reserve(10);
        }
    };
    
    std::array<BlockList, num_pools> pools;
    std::set<void*> mCleanup;    
};




int main()
{
    Pool pool;
    
    std::vector<void*> allocs;
    
    for (auto i = 10; i<= 4000; i = i * 1.3)
    {
        allocs.push_back(pool.allocate(i));
        pool.print();
    }
    
    auto it = allocs.begin();
    
    for (auto i = 10; i<= 4000; i = i * 1.3)
    {
        pool.deallocate(*it++, i);
        pool.print();
    }
}

