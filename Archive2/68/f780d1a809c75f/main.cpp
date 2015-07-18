#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <new>
#include <vector>



struct Pool
{   
    void* allocate(std::size_t n)
    {
        n = nextpow2(n);

            //std::cout << "alloc " << n << std::endl;
        
        if (n == 0 || n > (alignment * (1 << num_pools)))
        {

            //std::cout << "ERR NEW " << n << std::endl;
            return ::operator new(n);
        }
        
        
        auto pool_index = get_pool_index(n);    
        //assert(pool_index < num_pools);
        if (pool_index >= num_pools)
        {
            //std::cout << "NEW " << n << std::endl;
            return ::operator new(n);
        }
        
        auto& pool = pools[pool_index];
        
        if (!pool.empty())
        {
            auto result = pool.back();
            pool.pop_back();
            return result;
        }
        
        auto result = static_cast<char*>(allocate(n * 2));
        pool.push_back(result + n);
        return result;
    }
    
    void deallocate(void* ptr, std::size_t n)
    {

        n = nextpow2(n);

            //std::cout << "dealloc " << n << std::endl;
        if (n == 0 || n > (alignment * (1 << num_pools)))
        {

            //std::cout << "ERRRO delete " << n << std::endl;
            ::operator delete(ptr);
            return;
        }

        n = align(n);
        
        auto pool_index = get_pool_index(n);    
        //assert(pool_index < num_pools);
        if (pool_index >= num_pools)
        {

            //std::cout << "delete " << n << std::endl;
            ::operator delete(ptr);
            return;
        }
        
        auto& pool = pools[pool_index];
        pool.push_back(static_cast<char*>(ptr));
    }
    
    // details:
    
    int log2(int x)
    {
        int y;
        asm ( "\tbsr %1, %0\n"
            : "=r"(y)
            : "r" (x));
        return y;
    }
    
    int nextpow2(int x)
    {
        if (x < 0)
        {
            return 0;
        }
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
        return n > 16 ? (log2(n) - 4) : 0;
    }
        
    void print_pools()
    {
        std::cout << "pools: ";
        auto block_size = 16;
    	for (auto& pool : pools)
    	{
    		std::cout << " " << pool.size();
    		block_size *= 2;
    	}
        std::cout << '\n';
    }

    enum { alignment = 16, num_pools = 5 };
    std::array<std::vector<char*>, num_pools> pools;

};



    
int main()
{
    struct Pool pool;
    std::vector<void*> ptrs;
    ptrs.push_back(pool.allocate(7)); pool.print_pools();
    ptrs.push_back(pool.allocate(15)); pool.print_pools();
    ptrs.push_back(pool.allocate(30)); pool.print_pools();
    ptrs.push_back(pool.allocate(48)); pool.print_pools();
    ptrs.push_back(pool.allocate(48)); pool.print_pools();
    ptrs.push_back(pool.allocate(123)); pool.print_pools();
    ptrs.push_back(pool.allocate(99)); pool.print_pools();
    ptrs.push_back(pool.allocate(123)); pool.print_pools();

    pool.deallocate(ptrs[0], 7); pool.print_pools();
    pool.deallocate(ptrs[1], 15); pool.print_pools();
    pool.deallocate(ptrs[2], 30); pool.print_pools();
    pool.deallocate(ptrs[3], 48); pool.print_pools();
    pool.deallocate(ptrs[4], 48); pool.print_pools();
    pool.deallocate(ptrs[5], 123); pool.print_pools();
    pool.deallocate(ptrs[6], 99); pool.print_pools();
    pool.deallocate(ptrs[7], 123); pool.print_pools();

}
