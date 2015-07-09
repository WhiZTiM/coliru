#include <new>
#include <iostream>


// circular pool which allows sequential allocation
// if the pool is full then we allocate a new one double the size
// since we can't delete the old pool at that point we simply leak it
// once the pool is large enough no reallocations will occur.
// so there should only be a little bit of leakage
// during program startup when optimal pool sizes have not yet been determined
unsigned pool_size = 64;
void* pool_buffer = ::operator new(pool_size);
unsigned pool_used = 0;
unsigned pool_freed = 0;
unsigned total_allocations = 0;


void* allocate(unsigned n) // assume n is max aligned
{
    if (pool_used + n - pool_freed > pool_size)
    {
        pool_buffer = ::operator new (pool_size *= 2); // leak old pool
        pool_freed = -(pool_used - pool_freed);
        pool_used = 0;
    }
    
    auto result = static_cast<char*>(pool_buffer) + pool_used;
    pool_used += n;
    total_allocations++;
    return result;
}


void deallocate(void*, unsigned n)
{
    pool_freed += n;
}


int main()
{
    return long(allocate(123));
}