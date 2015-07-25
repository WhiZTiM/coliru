#include <cassert>
#include <iostream>


#define PRINT() print_impl(__FUNCTION__);


struct circular_buffer
{
    circular_buffer() : mStorage(new uint16_t[capacity()])
    {
        std::cout << "\n***********\n";
        PRINT();
    }
    
    
    static constexpr std::size_t capacity()
    {
        return 32;
    }
    
    void push_back(uint16_t value)
    {
        if (mSize == capacity())
        {
            mStorage[mBegin++ % capacity()] = value;
        }
        else
        {
            mStorage[mSize++ % capacity()] = value;
        }
        PRINT();
    }
    
    uint16_t pop_back()
    {
        assert(size());
        
        auto result = mStorage[(mBegin + mSize - 1) % capacity()];
        mSize--;
        
        PRINT();
        return result;
    }
    
    void push_front(uint16_t value)
    {
        mStorage[--mBegin % capacity()] = value;
        if (mSize != capacity())
        {
            mSize++;
        }
        PRINT();
    }
    
    uint16_t pop_front()
    {
        assert(size());
        mSize--;
        auto result = mStorage[mBegin++ % capacity()];
        PRINT();
        return result;
    }
    
    std::size_t size() const
    {
        return mSize >= capacity() ? capacity() : mSize;
    }
    
    bool empty()
    {
        return !mSize;
    }
    
    struct iterator
    {
        iterator(circular_buffer& buf) :
            mStorage(buf.mStorage),
            mOffset(buf.mBegin)
        {
        }
        
        iterator(circular_buffer& buf, int) :
            mStorage(buf.mStorage),
            mOffset(buf.mBegin + buf.mSize)
        {
        }
        
        uint16_t& operator*()
        {
            return mStorage[mOffset % circular_buffer::capacity()];
        }
        
        bool operator<(iterator rhs)
        {
            return mOffset < rhs.mOffset;
        }
        
        bool operator==(iterator rhs)
        {
            return mOffset == rhs.mOffset;
        }
        
        bool operator!=(iterator rhs)
        {
            return !(*this == rhs);
        }
        
        iterator& operator++()
        {
            mOffset++;
            return *this;
        }
        
        uint16_t* mStorage;
        uint16_t mOffset = 0;
    };
    
    iterator begin()
    {
        return iterator(*this);
    }
    
    iterator end()
    {
        return iterator(*this, 0);
    }
    
    void print_impl(const char* f)
    {
        std::cout << f
            << ": mSize=" << int(mSize)
            << " mBegin=" << int(mBegin)
            
            << " size()=" << size()
            << " capacity()=" << capacity()
            << " [";
            
            
            
        for (auto el : *this)
        {
            std::cout << el;
        }
        std::cout << "]" << std::endl;
    }
    
    uint16_t* mStorage; // max-index is 255, capacity is     
    uint32_t mBegin = 0;
    uint32_t mSize = 0;
};


int main()
{
    {
        circular_buffer buf;
        assert(buf.empty());
        buf.push_front(1);
        buf.push_front(2);
        buf.push_front(3);
        buf.pop_front();
        buf.pop_front();
        buf.pop_front();
        assert(buf.empty());
    }
    
    {
        circular_buffer buf;
        assert(buf.empty());
        buf.push_front(1);
        buf.push_front(2);
        buf.push_front(3);
        buf.pop_back();
        buf.pop_back();
        buf.pop_back();
        assert(buf.empty());
    }
    
    {
        circular_buffer buf;
        assert(buf.empty());
        buf.push_back(1);
        buf.push_back(2);
        buf.push_back(3);
        buf.pop_back();
        buf.pop_back();
        buf.pop_back();
        assert(buf.empty());
    }
    
    {
        circular_buffer buf;
        assert(buf.empty());
        
        buf.push_back(1);                                   assert(!buf.empty()); assert(buf.size() == 1);
        buf.push_back(2);                                   assert(!buf.empty()); assert(buf.size() == 2);
        buf.push_back(3);                                   assert(!buf.empty()); assert(buf.size() == 3);
        
        assert(!buf.empty()); assert(buf.size() == 3);      buf.pop_front(); 
        assert(!buf.empty()); assert(buf.size() == 2);      buf.pop_front(); 
        assert(!buf.empty()); assert(buf.size() == 1);      buf.pop_front();
        
        assert(buf.empty()) ; assert(buf.size() == 0);
    }
    
    {
        circular_buffer buf;
        for (auto i = 0; i != 40; ++i)
        {
            buf.push_back(i % 10);
        }
        
        while (buf.size() >= 2)
        {
            buf.pop_front();
            buf.pop_back();
        }
    }
    
    {
        circular_buffer buf;
        for (auto i = 0; i != 40; ++i)
        {
            buf.push_front(i % 10);
        }
        
        while (buf.size() >= 2)
        {
            buf.pop_front();
            buf.pop_back();
        }
    }
}
