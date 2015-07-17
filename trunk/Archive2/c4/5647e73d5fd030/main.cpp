#include <algorithm>
#include <array>
#include <iostream>
#include <new>
#include <vector>


#define TRACE std::cout << __FILE__ << ":" << __LINE__ << std::endl;


enum
{
    alignment = 16,
    num_pools = 10
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
    std::cout << "allocate(" << n << ") ";
    
    auto index = get_pool_index(n);    
    if (index >= num_pools)
    {
        std::cout << "::operator new(" << n << ")\n";
        return ::operator new(n);
    }
    
    auto& pool = pools[index];    
    
    if (!pool.empty())
    {
        auto result = pool.back();
        pool.pop_back();
        //std::cout << "reused " << n << std::endl;
        return result;
    }
    
    auto result = static_cast<char*>(allocate(n * 2));
    pool.push_back(result + n);
    //std::cout << "extra reserve for " << n << std::endl;
    return result;
}


void deallocate(void* ptr, std::size_t n)
{
    n = align(n);
    std::cout << "deallocate " << n << ' ';
    
    auto index = get_pool_index(n);    
    if (index >= num_pools)
    {
        ::operator delete(ptr);
        std::cout << "::operator delete(" << ptr << ' ' << n << ")\n";
    }
    
    auto& pool = pools[index];    
    pool.push_back(static_cast<char*>(ptr));

    //std::cout << "recycled  " << n << std::endl;
	std::cout << std::endl;
}


	auto print_pools = [&]
	{
		std::cout << "<pools>\n";
		auto block_size = 16;
		for (auto& pool : pools)
		{
			std::cout << "pool[" << (&pool - &pools[0]) << " -> " << block_size << "]=" << pool.size() << '\n';
			block_size *= 2;
		}
		std::cout << "</pools>\n";
	};
    
int main()
{
    std::vector<void*> allocations;
    std::vector<int> allocation_sizes;
    for (auto i = 1; i != 1000; ++i)
    {
		std::cout << '\n' << i << ":\n";
        allocations.push_back(allocate(i));
        allocation_sizes.push_back(align(i));
        
if (i % 4 == 0)
	print_pools();
        
        if (rand() % 10 == 0)
        {
            auto allocation_sizes_copy = allocation_sizes;
            std::random_shuffle(allocation_sizes_copy.begin(), allocation_sizes_copy.end());
            for (auto i = 0u; i < 2 * allocations.size() / 3; ++i)
            {
                auto& item = allocations[i];
                auto& size = allocation_sizes_copy[i];
                deallocate(item, size);
                std::cout << "Deallocated item of size " << size << '\n';
            }
            allocations.clear();
        }
    }

	print_pools();
    
    std::cout << "END OF PROGRAM" << std::endl;
}
