#ifndef ArenaAllocator_H
#define ArenaAllocator_H

#include <cstddef>
#include <cassert>
#include <cstdio>


struct Arena
{
    
    enum : int
    {
        Capacity = 512 * 1024,
        Alignment = 16
    };
    
    Arena()  :
        ptr_(buf_)
    {
    }
    
    ~Arena()
    {
        ptr_ = nullptr;
    }
    
    Arena(const Arena&) = delete;
    Arena& operator=(const Arena&) = delete;

            
    char* allocate(std::size_t n)
    {
        assert(pointer_in_buffer(ptr_) && "ArenaAllocator has outlived Arena");
        
        if (ptr_ + n < buf_ + Capacity)
        {
            auto result = ptr_;
            ptr_ += n;
            return result;
        }
        else
        {
            return static_cast<char*>(::operator new(n));
        }
    }
    void deallocate(char* p, std::size_t n) noexcept
    {
        assert(pointer_in_buffer(ptr_) && "ArenaAllocator has outlived Arena");
        
        if (pointer_in_buffer(p))
        {
            if (p + n == ptr_)
            {
                ptr_ = p;
            }
        }
        else
        {
            ::operator delete(p);
        }
    }
     
    static constexpr std::size_t size()
    {
        return Capacity;
    }
    
    std::size_t used() const
    {
        return static_cast<std::size_t>(ptr_ - buf_);
    }
    
    void reset()
    {
        ptr_ = buf_;
    }
    
    
    bool pointer_in_buffer(char* p) noexcept
    {
        return buf_ <= p && p <= buf_ + Capacity;
    }
    
    static constexpr std::size_t Align(std::size_t n)
    {
        return (n + Alignment - 1) & ~(Alignment - 1);
    }
    
    char __attribute__((__aligned__(16))) buf_[Capacity];
    char* ptr_ = buf_;
};


__thread Arena* local_arena;


template <class T>
struct ArenaAllocator
{
    typedef T value_type;

    template <class U>
    struct rebind
    {
        typedef ArenaAllocator<U> other;
    };

    ArenaAllocator() noexcept {}

    template <class U>
    ArenaAllocator(const ArenaAllocator<U>& ) noexcept {}
    
    ArenaAllocator(const ArenaAllocator&) = default;
    ArenaAllocator& operator=(const ArenaAllocator&) = delete;

    T* allocate(std::size_t n)
    {
        int alloc_size = Arena::Align(n * sizeof(T));
        return static_cast<T*>(static_cast<void*>(local_arena->allocate(alloc_size)));
    }
    
    void deallocate(T* p, std::size_t n) noexcept
    {
        int alloc_size = Arena::Align(n * sizeof(T));
        local_arena->deallocate(static_cast<char*>(static_cast<void*>(p)), alloc_size);
    }

    template<typename U>
    friend bool operator==(const ArenaAllocator& x, const ArenaAllocator<U>& y) noexcept
    {
        return true;
    }
    
    template<class U>
    friend bool operator!=(const ArenaAllocator& x, const ArenaAllocator<U>& y) noexcept
    {
        return !(x == y);
    }

    template <class U>
    friend class ArenaAllocator;
};



#endif  // ArenaAllocator_H



#include <memory>
#include <vector>




int main()
{
    for (int i = 0; i != 10; ++i)
    {
        std::unique_ptr<Arena> arena(local_arena = new Arena);
        std::vector<char, ArenaAllocator<char>> vec;
        std::vector<short, ArenaAllocator<short>> vec2;
        std::vector<int, ArenaAllocator<int>> vec3;
        std::vector<long, ArenaAllocator<long>> vec4;
        
        auto b = rand() % 100;
        auto e = b + 10 + rand() % 100000;
        for (int i = b; i < e; i += rand() % 10)
        {
            if (rand() % 3 == 0) vec.push_back(i);
            if (rand() % 3 == 0) vec2.push_back(i);
            if (rand() % 3 == 0) vec3.push_back(i);
            if (rand() % 3 == 0) vec4.push_back(i);
        }
        printf("Pool usage: %d/%d.\n", (int)local_arena->used(), (int)local_arena->size());
    }
}
