#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>



        
    template<typename T>
    struct TaggedPtr
    {
        T* operator->() { return t; }
        std::uint16_t tag() const { return 0; }
        
        template<typename F>
        void update_tag(F&& f) { (void)f; }
        T* t;
    };


template<typename T, std::uint16_t Capacity>
struct static_deque
{
    
    struct iterator
    {
        iterator() : deq_(), offset_() {}
        
        iterator(static_deque& deq) :
            deq_(&deq),
            offset_(deq.offset_)
        {
            std::cout << "iterator: offset=" << offset_ << " == end?" << (*this == iterator()) << std::endl;
        }

        T& operator*()
        {
            assert(offset_ < 100);
            return deq_->storage_[offset_ % Capacity];
        }
        
        T* operator->()
        {
            assert(offset_ < 100);
            return &deq_->storage_[offset_ % Capacity];
        }

        iterator& operator++()
        {
            offset_ = (offset_ + 1) % Capacity;
            return *this;
        }

        friend bool operator==(iterator lhs, iterator rhs)
        {
            return lhs.deq_ == rhs.deq_ && lhs.offset_ == rhs.offset_;
        }

        friend bool operator!=(iterator lhs, iterator rhs)
        {
            return !(lhs == rhs);
        }

        static_deque* deq_;
        std::uint16_t offset_;
    };

    iterator begin()
    {
        return iterator(*this);
    }

    iterator end()
    {
        return iterator();
    }

    void push(const T& t)
    {
        assert(size() < Capacity);
        auto i = (offset_ + size_) % Capacity;
        std::cout << "push at " << i << std::endl;
        storage_[i] = t;
        size_++;
    }

    T pop()
    {
        --size_;
        T& t = storage_[offset_++ % Capacity];
        T result = std::move(t);
        t.~T();
        return result;
    }
    
    constexpr std::size_t capacity() const
    {
        return Capacity;
    }
    
    std::size_t size() const
    {
        return size_;
    }
    
    std::uint16_t offset_ = 0;
    std::uint16_t size_ = 0;
    std::array<T, Capacity> storage_{};
};



template<typename Container>
void print(Container& c)
{
    std::cout << c.size();
    for (auto& el : c)
    {
        std::cout << el << ' ';
    }
    std::cout << std::endl;
}


int main()
{
    static_deque<int, 10> d;
    
    for (int i = 0; i != 20; ++i)
    {
        std::cout << "Pushing " << i << std::endl;
        d.push(i);
        print(d);
    }
}