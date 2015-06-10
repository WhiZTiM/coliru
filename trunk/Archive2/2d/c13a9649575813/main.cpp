#ifndef StackAllocator_H
#define StackAllocator_H

#include <algorithm>
#include <cstddef>
#include <cassert>
#include <cstdio>


template <class T>
struct StackAllocator;


struct StackStorage
{
    template<typename T>
    struct Allocator
    {
        typedef StackAllocator<T> type;
    };
    
    enum : int
    {
        Capacity = 1024 * 1024,
        alignment = 8
    };
    
    StackStorage()  :
        ptr_(buf_)
    {
    }
    
    ~StackStorage()
    {
        ptr_ = nullptr;
    }
    
    StackStorage(const StackStorage&) = delete;
    StackStorage& operator=(const StackStorage&) = delete;

            
    char* allocate(std::size_t n)
    {
        assert(pointer_in_buffer(ptr_) && "StackAllocator has outlived StackStorage");
        
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
                printf("deallocate\n");
        assert(pointer_in_buffer(ptr_) && "StackAllocator has outlived StackStorage");
        
        if (pointer_in_buffer(p))
        {
            if (p + n == ptr_)
            {
                ptr_ = p;
                if (ptr_ == buf_ + freed_)
                {
                    printf("Lucky all freed\n");
                    ptr_ = buf_;
                    freed_ = 0;
                }
                else
                {
                    printf("Lucky one freed. Unfreed=%d\n", (int)(int(ptr_ - buf_) - freed_));
                }
            }
            else
            {
                freed_ += n;
                if (buf_ + freed_ == ptr_)
                {
                    ptr_ = buf_;
                    freed_ = 0;
                    printf("Free from desize\n");
                }
                else
                {
                    printf("BORING Freed=%d Unfreed=%d\n", (int)freed_, (int)((ptr_ - buf_) - freed_));
                }
            }
        }
        else
        {
                printf("deleted freed\n");
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
        printf("pointer_in_buffer: p=%d\n", (int)(p - buf_));
        return buf_ <= p && p <= buf_ + Capacity;
    }
    
    
    char __attribute__((__aligned__(8))) buf_[Capacity];
    char* ptr_ = buf_;
    unsigned freed_ = 0;
};






StackStorage* global_storage;
        
template <class T>
struct StackAllocator
{
    typedef T value_type;

    template <class U>
    struct rebind
    {
        typedef StackAllocator<U> other;
    };

    StackAllocator() noexcept {}

    template <class U>
    StackAllocator(const StackAllocator<U>& ) noexcept {}
    
    StackAllocator(const StackAllocator&) = default;
    StackAllocator& operator=(const StackAllocator&) = delete;

    T* allocate(std::size_t n)
    {
        int alloc_size = (n * sizeof(T) + 7) & ~7;
        int index = (n * sizeof(T)) / 8;
        printf("StackAllocator::allocate n=%d sizeof(T)=%d alloc_size=%d index=%d\n", (int)n, (int)sizeof(T), (int)alloc_size, (int)index);
        if (index < 512)
        {
            return reinterpret_cast<T*>(global_storage[index].allocate(alloc_size));
        }
        else
        {
            return (T*)operator new(alloc_size);
        }
    }
    
    void deallocate(T* p, std::size_t n) noexcept
    {
        int alloc_size = (n * sizeof(T) + 7) & ~7;
        int index = (n * sizeof(T)) / 8;
        printf("StackAllocator::deallocate n=%d sizeof(T)=%d alloc_size=%d index=%d\n", (int)n, (int)sizeof(T), (int)alloc_size, (int)index);
        if (index < 512)
        {
            global_storage[index].deallocate(reinterpret_cast<char*>(p), alloc_size);
        }
        else
        {
            operator delete(p);
        }
    }

    template<typename U>
    friend bool operator==(const StackAllocator& x, const StackAllocator<U>& y) noexcept
    {
        return true;
    }
    
    template<class U>
    friend bool operator!=(const StackAllocator& x, const StackAllocator<U>& y) noexcept
    {
        return !(x == y);
    }

    template <class U>
    friend class StackAllocator;
};



#endif  // StackAllocator_H



#include <vector>




int main()
{
    global_storage = new StackStorage[512];
    {
    std::vector<char, StackAllocator<char>> vec;
    std::vector<char, StackAllocator<char>> vec2(1);
    std::vector<char, StackAllocator<char>> vec3(2);
    std::vector<char, StackAllocator<char>> vec4(3);
    
    for (int i = 0; i != 1000; ++i)
    {
        vec.push_back(i);
        vec2.push_back(i);
        vec3.push_back(i);
        vec4.push_back(i);

        if (i % 10 == 0)
        {
            printf("==== BEGIN CLEANUP ====\n");
            decltype(vec)().swap(vec);
            decltype(vec2)().swap(vec2);
            decltype(vec3)().swap(vec3);
            decltype(vec4)().swap(vec4);
            printf("==== END CLEANUP ====\n");
        }
    }
    }
}
