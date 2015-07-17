#include <algorithm>
#include <array>
#include <iostream>
#include <new>
#include <vector>


enum
{
    alignment = 16,
    num_pools = 9
};

std::array<std::vector<char*>, num_pools> pools;



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



void* allocate(std::size_t n)
{
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
    n = align(n);
    
    auto index = get_pool_index(n);    
    if (index >= num_pools)
    {
        ::operator delete(ptr);
    }
    
    auto& pool = pools[index];    
    pool.push_back(static_cast<char*>(ptr));
}


auto num_allocations = 0;
auto num_deallocations = 0;


void print_pools()
{
	std::cout << "<pools>\n";
    std::cout << "  allocations=" << num_allocations << "\n  deallocations=" << num_deallocations << "\n";
	auto block_size = 16;
	for (auto& pool : pools)
	{
		std::cout << "  pool<" << block_size << ">=" << pool.size() << '\n';
		block_size *= 2;
	}
	std::cout << "</pools>\n";
}

    
int main()
{
    std::vector<void*> allocations;
    std::vector<int> allocation_sizes;
    auto block_size = 16;
    for (auto i = 1; i <= 9; ++i)
    {
        allocations.push_back(allocate(block_size));
        allocations.push_back(allocate(block_size));
        allocations.push_back(allocate(block_size));
        num_allocations += 3;
        
        allocation_sizes.push_back(align(block_size));
        allocation_sizes.push_back(align(block_size));
        allocation_sizes.push_back(align(block_size));
        
        block_size *= 2;
            
        print_pools();

        if (!allocations.empty() && rand() % 4 == 0)
        {
            if (allocations.size() % 2 == 0)
            {
                // deallocate from the front
                deallocate(allocations.front(), allocation_sizes.front());
                allocations.erase(allocations.begin());
                allocation_sizes.erase(allocation_sizes.begin());
            }
            else
            {
                // deallocate from the end
                deallocate(allocations.back(), allocation_sizes.back());
                allocations.pop_back();
                allocation_sizes.pop_back();
            }
            
            print_pools();
            num_deallocations++;
        }
        
    }

    while (!allocations.empty())
    {
        print_pools();
            if (allocations.size() % 2 == 0)
            {
                // deallocate from the front
                deallocate(allocations.front(), allocation_sizes.front());
                allocations.erase(allocations.begin());
                allocation_sizes.erase(allocation_sizes.begin());
            }
            else
            {
                // deallocate from the end
                deallocate(allocations.back(), allocation_sizes.back());
                allocations.pop_back();
                allocation_sizes.pop_back();
            }
        num_deallocations++;
    }

    print_pools();    
    std::cout << "END OF PROGRAM" << std::endl;
}
