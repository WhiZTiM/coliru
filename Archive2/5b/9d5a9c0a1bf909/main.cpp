#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <array>
#include <cassert>
#include <vector>
#include <iostream>



template<typename T, int SmallCapacity = 10>
struct Vector
{
    Vector() : variant_(SmallVector()) {}
    
    Vector(std::size_t size) : variant_(size <= SmallCapacity ? Variant(SmallVector(size)) : Variant(BigVector(size)))
    {
    }
    
    Vector(std::initializer_list<T> list) :
        variant_(list.size() <= SmallCapacity ? SmallVector(list) : std::vector<T>(list))
    {
    }
    
    using iterator = T*;
    
    const T& operator[](std::size_t i) const
    {
        return data()[i];
    }
    
    
    T& operator[](std::size_t i)
    {
        return const_cast<T&>(static_cast<const Vector&>(*this)[i]);
    }
    
    
    void push_back(T&& t)
    {
        if (auto small = boost::get<SmallVector>(&variant_))
        {
            if (small->size() < small->capacity())
            {
                small->push_back(std::move(t));
            }
            else
            {
                std::cout << "size(" << small->size() << ") == capacity(" << small->capacity() << ") => switching to dynamic allocation." << std::endl;
                BigVector big;
                big.reserve(small->capacity() + 1);
                for (auto& el : *small)
                {
                    big.push_back(std::move(el));
                }
                big.push_back(std::move(t));
                variant_ = std::move(big);
                return;
            }
        }
        else
        {
            auto& big = boost::get<BigVector>(variant_);
            big.push_back(std::move(t));
        }
    }
    
    void push_back(const T& t)    
    {
        push_back(T(t));
    }
    
    const T* data() const
    {
        if (auto small = boost::get<SmallVector>(&variant_)) return small->data();
        return &*boost::get<BigVector>(variant_).data();
    }
    
    T* begin()
    {
        if (auto small = boost::get<SmallVector>(&variant_)) return small->begin();
        return &*boost::get<BigVector>(variant_).begin();
    }
    
    T* end()
    {
        if (auto small = boost::get<SmallVector>(&variant_)) return small->end();
        return &*boost::get<BigVector>(variant_).end();
    }
    
    std::size_t size() const
    {
        if (auto small = boost::get<SmallVector>(&variant_)) return small->size();
        return boost::get<BigVector>(variant_).size();
    }
    
    struct SmallVector
    {
        SmallVector() : size_(), array_() {}
        SmallVector(std::size_t size) : size_(size), array_() {}
        
        SmallVector(std::initializer_list<T> list) :
            size_(list.size()),
            array_(list)
        {
        }
        
        void push_back(T&& t)
        {
            array_[size_++] = std::move(t);
        }
        
        const T* data() const { return &array_[0]; }
        const T* begin() const { return data(); }
        const T* end() const { return begin() + size(); }
        
        T* data() { return &array_[0]; }
        T* begin() { return data(); }
        T* end() { return begin() + size(); }
        
        const T& operator[](std::size_t i) const { return array_[i]; }
        T& operator[](std::size_t i) { return array_[i]; }
        
        std::size_t size() const { return size_; }
        
        constexpr std::size_t capacity() const { return SmallCapacity; }
        
        uint8_t size_;
        std::array<T, SmallCapacity> array_;
    };
    using BigVector = std::vector<T>;
    using Variant = boost::variant<SmallVector, std::vector<T>>;
    boost::variant<SmallVector, std::vector<T>> variant_;
};


template<typename T, typename U, int SmallCapacity>
struct Map
{
    Map(std::initializer_list<std::pair<T, U>> list) :
        pair_(Vector<T, SmallCapacity>(list.size()), Vector<U, SmallCapacity>(list.size()))
    {
        for (auto& pair : list)
        {
            auto i = &pair - &*list.begin();
            pair_.first[i] = std::move(pair.first);
            pair_.second[i] = std::move(pair.second);
        }
    }
    
    struct iterator
    {
        using FirstIt = typename Vector<T, SmallCapacity>::iterator;
        using SecondIt = typename Vector<U, SmallCapacity>::iterator;
        
        struct First
        {
            First(FirstIt it) : it(it) {}
            operator const T&() const { return *it; }
            operator T&() { return *it; }
            bool operator==(const First& rhs) { return it == rhs.it; }
            bool operator!=(const First& rhs) { return it != rhs.it; }
            FirstIt it;
        };
        
        struct Second
        {
            Second(SecondIt it) : it(it) {}
            operator const T&() const { return *it; }
            operator T&() { return *it; }
            bool operator==(const Second& rhs) { return it == rhs.it; }
            bool operator!=(const Second& rhs) { return it != rhs.it; }
            SecondIt it;
        };
        
        using Pair = std::pair<First, Second>;
        
        iterator(FirstIt first, SecondIt second) : pair_(first, second)
        {
            //std::cout << "iterator " << *first << " " << *second << std::endl;
        }   
        
        Pair& operator *() { return pair_; }        
        Pair* operator->() { return &pair_; }        
        
        bool operator==(const iterator& rhs) const { return pair_ == rhs.pair_; }        
        bool operator!=(const iterator& rhs) const { return pair_ != rhs.pair_; }
        
        iterator& operator++()
        {
            ++pair_.first.it;
            ++pair_.second.it;
            return *this;
        }
        
        Pair pair_;
    };
    
    iterator begin()
    {
        return iterator(pair_.first.begin(), pair_.second.begin());
    }
    
    iterator end()
    {
        return iterator(pair_.first.end(), pair_.second.end());
    }    

    std::size_t size() const
    {
        return pair_.first.size();
    }

    
    using Pair = std::pair<Vector<T, SmallCapacity>, Vector<U, SmallCapacity>>;
    Pair pair_;
};


int main()
{
    Vector<int, 4> vec;
    for (int i = 0; i != 20; ++i)
    {
        std::cout << i << ' ' << std::flush;
        vec.push_back(i);        
        std::cout << "\t";
        for (auto i : vec) std::cout << i << ' ';
        std::cout << std::endl;
    }
    
    Map<int, int, 10> map = {
        { 1, 1 * 2 },
        { 2, 2 * 2 },
        { 3, 3 * 2 },
        { 4, 4 * 2 },
        { 5, 5 * 2 },
        { 6, 6 * 2 },
        { 7, 7 * 2 },
        { 8, 8 * 2 },
        { 9, 9 * 2 },
        { 10, 10 * 2 }
    };
    
    
    std::cout << "Iterating over the map of size " << map.size() << std::endl;
    assert(map.begin() != map.end());
    for (auto i = map.begin(), e = map.end(); i != e; ++i) std::cout << i->first << '-' << i->second << ' '; std::cout << std::endl;
    for (auto i = map.begin(), e = map.end(); i != e; ++i) std::cout << i->first << '-' << i->second << ' '; std::cout << std::endl;
    for (auto i = map.begin(), e = map.end(); i != e; ++i) std::cout << i->first << '-' << i->second << ' '; std::cout << std::endl;
    for (auto i = map.begin(), e = map.end(); i != e; ++i) std::cout << i->first << '-' << i->second << ' '; std::cout << std::endl;
    for (auto i = map.begin(), e = map.end(); i != e; ++i) std::cout << i->first << '-' << i->second << ' '; std::cout << std::endl;
    for (auto i = map.begin(), e = map.end(); i != e; ++i) std::cout << i->first << '-' << i->second << ' '; std::cout << std::endl;
    for (auto i = map.begin(), e = map.end(); i != e; ++i) std::cout << i->first << '-' << i->second << ' '; std::cout << std::endl;
    for (auto i = map.begin(), e = map.end(); i != e; ++i) std::cout << i->first << '-' << i->second << ' '; std::cout << std::endl;
}
