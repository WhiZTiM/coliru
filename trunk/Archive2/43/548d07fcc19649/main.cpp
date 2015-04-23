#include <array>
#include <cstdint>


        
    template<typename T>
    struct TaggedPtr
    {
        T* operator->() { return t; }
        std::uint16_t tag() const { return 0; }
        
        template<typename F>
        void update_tag(F&& f) { (void)f; }
        T* t;
    };


template<typename T, std::uint16_t N>
struct static_deque
{
    struct iterator
    {
        iterator(static_deque& d) : d(&d)
        {
        }

        T& operator*()
        {
            return d[d.tag()];
        }

        iterator& operator++()
        {
            d.update_tag([](std::uint16_t& tag) {
                if (++tag == N) tag = 0;
            });
            return *this;
        }

        friend bool operator==(iterator lhs, iterator rhs)
        {
            return lhs.mIndex == rhs.mIndex;
        }

        friend bool operator!=(iterator lhs, iterator rhs)
        {
            return !(lhs == rhs);
        }

        TaggedPtr<static_deque> d;
    };

    iterator begin()
    {
        return &mStorage[mOffset];
    }

    iterator end()
    {
        return &mStorage[(mOffset + mSize) % N];
    }

    void push(const T& t)
    {
        mStorage[(mOffset + mSize++) % N] = t;
    }

    void push(T&& t)
    {
        mStorage[(mOffset + mSize++) % N] = std::move(t);
    }

    T pop()
    {
        --mSize;
        T& t = mStorage[mOffset++ % N];
        T result = std::move(t);
        t.~T();
        return result;
    }
    
    std::uint16_t mOffset;
    std::uint16_t mSize;
    std::array<T, N> mStorage;
};

