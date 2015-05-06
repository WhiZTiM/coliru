#include <boost/lockfree/stack.hpp>
#include <iostream>
#include <vector>
#include <mutex>
#include <sstream>
#include <thread>


struct LogItem
{
    ~LogItem()
    {
        static std::mutex m;
        std::lock_guard<std::mutex> l(m);
        std::cout << ss.str() << std::endl;
    }

    std::ostringstream ss;
};
#define LOG() if (0) ; else LogItem().ss

    static long sane_thread_id()
    {
        static std::atomic<long> counter{0};
        static __thread const long id = counter++;
        return id;
    }
    

template<typename T>
struct Pool
{
    T* allocate(std::size_t n)
    {
        assert(n > 0);
        if (n > 1) return new (malloc(sizeof(T) * n)) T;
        auto poolIndex = sane_thread_id() % num_pools;
        return mLocalPools[poolIndex].allocate();
    }

    void deallocate(T* t, std::size_t n)
    {
        if (n > 1)
        {
            free(t);
            return;
        }
        LocalPool::GetBlock(t)->release();
    }

    struct LocalPool
    {
        enum { Capacity = 100 };


        struct Storage
        {
            T* storage()
            {
                return static_cast<T*>(static_cast<void*>(&mStorage));
            }
    
            typename std::aligned_storage<sizeof(T), alignof(T)>::type mStorage;
        };
    
        struct Block
        {
            explicit Block(LocalPool* inLocalPool) :
                mLocalPool(inLocalPool)
            {
            }
    
            T* storage()
            {
                return mStorage.storage();
            }

            void release()
            {
                if (!mLocalPool)
                {
                    free(this);
                    return;
                }
                if (!mLocalPool->mStack.push(this))
                {
                    assert(false);
                }
            }
        
            LocalPool* mLocalPool;
            Storage mStorage;
        };
    
        static Block* GetBlock(T* obj)
        {
            return reinterpret_cast<Block*>(reinterpret_cast<LocalPool**>(obj) - 1);
        }

        LocalPool()
        {
            for (int i = 0; i != Capacity; ++i)
            {
                T* t = mallocate();
                auto block = GetBlock(t);
                block->mLocalPool = this;
                mStack.push(block);
            }
        }


        ~LocalPool()
        {
            Block* block;
            auto counter = 0;
            while (mStack.pop(block))
            {
                counter++;
                free(block);
            }
            LOG() << "Freed " << counter << '/' << Capacity;
        }
        
        T* allocate()
        {
            Block* result;
            if (mStack.pop(result))
            {
                return result->storage();
            }
            LOG() << "MALLOCATE";
            return mallocate();
        }
        
        T* mallocate()
        {
            auto block = new (malloc(sizeof(Block))) Block(nullptr);
            return block->storage();
        }

        boost::lockfree::stack<Block*, boost::lockfree::capacity<Capacity>> mStack;
    };
    
    enum { num_pools = 32 };
    LocalPool mLocalPools[num_pools];
};



// Create STL-compatible allocator for objects of type T using custom storage type.
template<template<typename> class Storage, typename T>
struct BasicAllocator
{
    typedef T * pointer;
    typedef const T * const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    template<typename U>
    struct rebind
    {
        typedef BasicAllocator<Storage, U> other;
    };

    BasicAllocator() : mStorage() {}

    BasicAllocator(Storage<T>& inStorage) :
        mStorage(&inStorage)
    {
        assert(mStorage);
    }

    template<typename U>
    BasicAllocator(const BasicAllocator<Storage, U>& rhs) :
        mStorage(rhs.mStorage)
    {
        assert(mStorage);
    }

    template<typename U>
    BasicAllocator& operator=(const BasicAllocator<Storage, U>& rhs)
    {
        assert(mStorage);
        mStorage = rhs.mStorage;
        return *this;
    }

    ~BasicAllocator()
    {
    }

    const T* address(const T& s) const { return &s; }
    T* address(T& r) const { return &r; }

    size_t max_size() const { return std::size_t(-1); }

    bool operator==(const BasicAllocator& rhs) const { return mStorage == rhs.mStorage; }
    bool operator!=(const BasicAllocator& rhs) const { return mStorage != rhs.mStorage; }

    template<typename U, typename ...Args>
    void construct(U* p, Args&& ...args) const
    {
        assert(p);
        new ((void*)p) U(std::forward<Args>(args)...);
    }

    void destroy(T * const p) const
    {
        p->~T();
    }

    T * allocate(size_t n) const
    {
        assert(n);
        assert(mStorage);
        return static_cast<T*>(mStorage->allocate(n));
    }

    void deallocate(T * const p, const size_t n) const
    {
        assert(n);
        assert(mStorage);
        mStorage->deallocate(p, n);
    }

    template <typename U>
    T * allocate(const size_t n, const U*) const
    {
        return this->allocate(n);
    }

    //using propagate_on_container_copy_assignment = std::true_type;
    //using propagate_on_container_move_assignment = std::true_type;

    Storage<T>* mStorage;
};



int main()
{
    Pool<int> pool_;
    
    BasicAllocator<Pool, int> allocator(pool_);
    auto task = [&allocator]{
        std::vector<int*> allocs;
        allocs.reserve(100);
        for (int i = 0; i != 102; ++i) {
            allocs.push_back(new (allocator.allocate(1)) int(i));
        }
        //std::random_shuffle(allocs.begin(), allocs.end());
        for (auto& ptr : allocs) {
            allocator.deallocate(ptr, 1);
        }
        std::stringstream ss;
        ss << sane_thread_id() << ":";
        allocs.clear();
        for (int i = 0; i != 100; ++i) {
            auto& n = *((int*)allocator.allocate(1));
            ss << n << ' ';
            allocs.push_back(&n);
        }
        for (auto& alloc : allocs) {
            allocator.deallocate(alloc, 1);
        }
        LOG() << ss.str();
    };


    {
        auto n2 = allocator.allocate(2);
        auto n3 = allocator.allocate(3);
        allocatator.deallocate(n2, 2);
        allocatator.deallocate(n3, 3);
    }

    {
        auto n2 = allocator.allocate(2);
        auto n3 = allocator.allocate(3);
        allocatator.deallocate(n3, 3);
        allocatator.deallocate(n2, 2);
    }

    std::thread t1(task), t2(task), t3(task);
    t1.join(), t2.join(), t3.join();
}
