#include <vector>
#include <array>
#include <iostream>


struct Pool
{
    void* allocate(std::size_t n)
    {
        auto aligned_n = nextpow2(align(n));        
        std::cout << "allocate:" << aligned_n << std::endl;
        auto pool_index = get_pool_index(aligned_n);
        return do_allocate(aligned_n, pool_index);
    }
    
    void deallocate(void* ptr, std::size_t n)
    {
        auto aligned_n = nextpow2(align(n));
        std::cout << "deallocate:" << aligned_n << std::endl;
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
        if (pool_index >= num_pools)
        {
            std::cout << "operator new(" << n << ")\n";
            return ::operator new(n);
        }

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

    void do_deallocate(void* ptr, std::size_t n, std::size_t pool_index)
    {
        if (pool_index >= num_pools)
        {
            ::operator delete(ptr);
            return;
        }

        auto& pool = pools[pool_index];
        pool.push_back(ptr);
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
    
    std::array<std::vector<void*>, num_pools> pools;
    
};


int main()
{
    Pool pool;
    auto a = pool.allocate(10); pool.print();
    auto c = pool.allocate(30); pool.print();
    auto d = pool.allocate(50); pool.print();
    auto e = pool.allocate(200); pool.print();
    auto f = pool.allocate(500); pool.print();
    auto g = pool.allocate(100); pool.print();
    auto h = pool.allocate(1000); pool.print();
    pool.deallocate(c, 30); pool.print();
    pool.deallocate(d, 50); pool.print();
    pool.deallocate(e, 200); pool.print();
    pool.deallocate(a, 10); pool.print();
    pool.deallocate(g, 100); pool.print();
    pool.deallocate(f, 500); pool.print();
    pool.deallocate(h, 1000); pool.print();
}

