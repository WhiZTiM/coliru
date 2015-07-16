#include <iostream>
#include <array>


template<std::size_t Alignment>
std::size_t align(std::size_t n)
{
    return (n + Alignment - 1) & ~(Alignment - 1);
}


struct Pool
{
    void* allocate(std::size_t n)
    {
        if (size_ == 0)
        {
            return ::operator new(n);
        }
        return blocks_[--size_];
    }
    
    void deallocate(void* ptr, std::size_t)
    {
        if (size_ == blocks_.size())
        {
            ::operator delete(ptr);
            return;
        }
        blocks_[size_++] = ptr;
    }
    
    std::array<void*, 100> blocks_;
    uint8_t size_ = 0;
};
    
    
Pool pool16[8];
Pool pool32[4];
Pool pool64[4];
Pool pool128[4];
Pool pool256[4];


void* allocate(std::size_t n)
{
    if (n <= 128)
    {
        n = align<16>(n);
        std::cout << n << " index=" << int(n / 16 - 1) << std::endl;
        return pool16[n / 16 - 1].allocate(n);
    }
    
    if (n <= 256)
    {
        n = align<32>(n);
        std::cout << n << " index=" << int((n - 128) / 32 - 1) << std::endl;
        return pool32[(n - 128) / 32 - 1].allocate(n);
    }
    
    if (n <= 512)
    {
        n = align<64>(n);
        std::cout << n << " index=" << int((n - 256) / 64 - 1) << std::endl;
        return pool64[(n - 256) / 64 - 1].allocate(n);
    }
    
    if (n <= 1024)
    {
        n = align<128>(n);
        std::cout << n << " index=" << int((n - 512) / 128 - 1) << std::endl;
        return pool128[(n - 512) / 128 - 1].allocate(n);
    }
    
    if (n <= 2048)
    {
        n = align<256>(n);
        std::cout << n << " index=" << int((n - 1024) / 256 - 1) << std::endl;
        return pool256[(n - 1024) / 256 - 1].allocate(n);
    }
    
    return ::operator new (n);
    
}


void deallocate(void* ptr, std::size_t n)
{
    if (n <= 128)
    {
        n = align<16>(n);
        std::cout << n << " index=" << int(n / 16 - 1) << std::endl;
        pool16[n / 16 - 1].deallocate(ptr, n);
        return;
    }
    
    if (n <= 256)
    {
        n = align<32>(n);
        std::cout << n << " index=" << int((n - 128) / 32 - 1) << std::endl;
        pool32[(n - 128) / 32 - 1].deallocate(ptr, n);
        return;
    }
    
    if (n <= 512)
    {
        n = align<64>(n);
        std::cout << n << " index=" << int((n - 256) / 64 - 1) << std::endl;
        pool64[(n - 256) / 64 - 1].deallocate(ptr, n);
        return;
    }
    
    if (n <= 1024)
    {
        n = align<128>(n);
        std::cout << n << " index=" << int((n - 512) / 128 - 1) << std::endl;
        pool128[(n - 512) / 128 - 1].deallocate(ptr, n);
        return;
    }
    
    if (n <= 2048)
    {
        n = align<256>(n);
        std::cout << n << " index=" << int((n - 1024) / 256 - 1) << std::endl;
        pool256[(n - 1024) / 256 - 1].deallocate(ptr, n);
        return;
    }
    
    ::operator delete(ptr);
    
}


int main()
{
    for (auto i = 16; i <= 3000; i += 8)
    {
        allocate(i);
    }
}

