#include <algorithm>
#include <array>
#include <iostream>
#include <new>
#include <vector>



struct Pool
{   
    void* allocate(std::size_t n)
    {
        num_allocations++;
        n = align(n);
        
        
        auto index = get_pool_index(n);    
        if (index >= num_pools)
        {
            return ::operator new(n);
        }
        
        auto& pool = pools[index];    
        
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
        num_deallocations++;
        n = align(n);
        
        auto index = get_pool_index(n);    
        if (index >= num_pools)
        {
            ::operator delete(ptr);
        }
        
        auto& pool = pools[index];    
        pool.push_back(static_cast<char*>(ptr));
    }
    
    // details:
    
    int Log2(int x)
    {
        int y;
        asm ( "\tbsr %1, %0\n"
            : "=r"(y)
            : "r" (x));
        return y;
    }
    
    std::size_t align(std::size_t n)
    {
        return (n + alignment - 1) & ~(alignment - 1);
    }
    
    std::size_t get_pool_index(std::size_t n)
    {
        return n <= 16 ? 0 : (Log2(n) - 4);
    }
        
    void print_pools()
    {
        std::cout << "<pools>\n";
        //std::cout << "  allocations=" << num_allocations << "\n  deallocations=" << num_deallocations << "\n";
    	auto block_size = 16;
    	for (auto& pool : pools)
    	{
    		std::cout << "  pool<" << block_size << ">=" << pool.size() << '\n';
    		block_size *= 2;
    	}
    	std::cout << "</pools>\n";
    }

    enum { alignment = 16, num_pools = 9 };
    std::array<std::vector<char*>, num_pools> pools;
        
    int num_allocations = 0;
    int num_deallocations = 0;

};



    
int main()
{
    struct Pool pool;
 
    // keep track of allocations. required for deallocation later
    std::vector<void*> allocations;
    std::vector<int> allocation_sizes;
    
    
    // initial allocation size
    auto block_size = 16;
    
    pool.print_pools();
            
    // allocation loop
    for (auto i = 1; i <= 9; ++i)
    {
        // allocate 3 blocks and store the sizes
        allocations.push_back(pool.allocate(block_size)); allocation_sizes.push_back(block_size);
        allocations.push_back(pool.allocate(block_size)); allocation_sizes.push_back(block_size);
        allocations.push_back(pool.allocate(block_size)); allocation_sizes.push_back(block_size);
        
        // set next allocation size
        block_size *= 2;
            
            
        pool.print_pools();
        
        
        
        if (i % 3 == 0) // maybe deallocate
        {
            if (allocations.empty()) continue;
            
            // randomize the deallocations (from the front or the back)
            if (allocations.size() % 2 == 0) 
            {
                // deallocate from the front
                pool.deallocate(allocations.front(), allocation_sizes.front());
                allocations.erase(allocations.begin());
                allocation_sizes.erase(allocation_sizes.begin());
            }
            else
            {
                // deallocate from the end                
                pool.deallocate(allocations.back(), allocation_sizes.back());
                allocations.pop_back();
                allocation_sizes.pop_back();
            }
            
            pool.print_pools();
        }
        
    }

    while (!allocations.empty())
    {
        pool.print_pools();
        if (allocations.size() % 2 == 0)
        {
            // deallocate from the front
            pool.deallocate(allocations.front(), allocation_sizes.front());
            allocations.erase(allocations.begin());
            allocation_sizes.erase(allocation_sizes.begin());
        }
        else
        {
            // deallocate from the end
            pool.deallocate(allocations.back(), allocation_sizes.back());
            allocations.pop_back();
            allocation_sizes.pop_back();
        }
    }

    pool.print_pools();    
    std::cout << "END OF PROGRAM" << std::endl;
}
