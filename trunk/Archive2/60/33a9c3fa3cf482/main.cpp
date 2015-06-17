#include <cstddef>


using BlockPtr = char*;

char __attribute__((__aligned__(128))) storage[4 * 1024 * 1024];
enum { max_size = 1024 };
std::vector<BlockPtr> blockss[128]



inline static std::size_t align(std::size_t n, std::size_t alignment)
{
    const auto alignment = n <= 8 ? 8 : 16;
    return (n + alignment - 1) & ~(alignment - 1);
}


void* Allocate(std::size_t n)
{
    n = align(n);
    auto& blocks = blockss[n];
    if (blocks.empty())
    {
        auto result = storage_offset + n;
        if (result < sizeof(storage))
        {
            storage_offset += n;
            auto result = storage_offset + n;
        }
    }
    if (storage_offset == 
    auto result = &storage[storage_offset];
    storage_offset += n;
}


void Deallocate(void* ptr, std::size_t n)
{
    n = align(n);
    
}