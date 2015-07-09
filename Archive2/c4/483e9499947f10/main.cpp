#include <new>
#include <array>
#include <iostream>


// Circular pool for sequential allocation.
// If the pool is full then we allocate a new one of twice the old size.
// Since we can't delete the old pool at that point we simply leak it.
// So there is leakage until a stable pool size has been determined.
// If you have sufficient RAM this is probalby not a big deal..
unsigned pool_size = 16;
void* pool_buffer = ::operator new(pool_size);
unsigned pool_used = 0;
unsigned pool_freed = 0;


void* allocate(unsigned n)
{
    n = (n + 15) & ~15;
    if (pool_used + n - pool_freed > pool_size)
    {
        std::cout << " ALLOCATE " << pool_size * 2 << "B (LEAKING " << pool_size << "B)\n";
        pool_buffer = ::operator new (pool_size *= 2); // leak old pool
        if (pool_freed < pool_used)
        {
            pool_freed = -(pool_used - pool_freed);
        }
        pool_used = 0;
    }
    
    auto result = static_cast<char*>(pool_buffer) + (pool_used % pool_size);
    pool_used += n;
    return result;
}


void deallocate(void*, unsigned n)
{
    std::cout << " freed=" << int(pool_freed + n) << '/' << pool_used;
    pool_freed += n;
    if (pool_freed == pool_used)
    {
        pool_freed = pool_used = 0;
        std::cout << " CLEAR!";
    }
    std::cout << '\n';
}


int main()
{
    
    std::array<void*, 100> allocs; 
    int n = 0;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    std::cout << "\nGarbage collection:\n"; for (int i = 0; i != n; ++i) deallocate(allocs[i], 16); n = 0; std::cout << "\n\nStart:\n";
    
    
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    std::cout << "\nGarbage collection:\n"; for (int i = 0; i != n; ++i) deallocate(allocs[i], 16); n = 0; std::cout << "\n\nStart:\n";
    
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    std::cout << "\nGarbage collection:\n"; for (int i = 0; i != n; ++i) deallocate(allocs[i], 16); n = 0; std::cout << "\n\nStart:\n";
    
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    std::cout << "\nGarbage collection:\n"; for (int i = 0; i != n; ++i) deallocate(allocs[i], 16); n = 0; std::cout << "\n\nStart:\n";
    
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    std::cout << "\nGarbage collection:\n"; for (int i = 0; i != n; ++i) deallocate(allocs[i], 16); n = 0; std::cout << "\n\nStart:\n";
    
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    std::cout << "\nGarbage collection:\n"; for (int i = 0; i != n; ++i) deallocate(allocs[i], 16); n = 0; std::cout << "\n\nStart:\n";
    
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    std::cout << "\nGarbage collection:\n"; for (int i = 0; i != n; ++i) deallocate(allocs[i], 16); n = 0; std::cout << "\n\nStart:\n";
    
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    std::cout << "\nGarbage collection:\n"; for (int i = 0; i != n; ++i) deallocate(allocs[i], 16); n = 0; std::cout << "\n\nStart:\n";
    
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    std::cout << "\nGarbage collection:\n"; for (int i = 0; i != n; ++i) deallocate(allocs[i], 16); n = 0; std::cout << "\n\nStart:\n";
    
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    std::cout << "\nGarbage collection:\n"; for (int i = 0; i != n; ++i) deallocate(allocs[i], 16); n = 0; std::cout << "\n\nStart:\n";
    
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    std::cout << "\nGarbage collection:\n"; for (int i = 0; i != n; ++i) deallocate(allocs[i], 16); n = 0; std::cout << "\n\nStart:\n";
    
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    std::cout << "\nGarbage collection:\n"; for (int i = 0; i != n; ++i) deallocate(allocs[i], 16); n = 0; std::cout << "\n\nStart:\n";
    
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    allocs[n++] = allocate(16); std::cout << " pool_used=" << pool_used << "/" << pool_size << " pool_freed=" << (int)pool_freed << " pool_size=" << pool_size << std::endl;
    std::cout << "\nGarbage collection:\n"; for (int i = 0; i != n; ++i) deallocate(allocs[i], 16); n = 0;
}

