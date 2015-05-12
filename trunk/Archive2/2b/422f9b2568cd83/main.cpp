#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <array>
#include <cassert>
#include <vector>
#include <iostream>



template<typename T, int SmallCapacity = 10>
struct Vector
{
    Vector() : mVariant()
    {
    }
    
    Vector(std::initializer_list<T> list) :
        mVariant(list.size() <= SmallCapacity ? SmallVector(list) : std::vector<T>(list))
    {
    }
    
    using iterator = T*;
    
    void push_back(T&& t)
    {
        if (auto small = boost::get<SmallVector>(&mVariant))
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
                mVariant = std::move(big);
                return;
            }
        }
        else
        {
            auto& big = boost::get<BigVector>(mVariant);
            big.push_back(std::move(t));
        }
    }
    
    void push_back(const T& t)    
    {
        push_back(T(t));
    }
    
    T* begin()
    {
        if (auto small = boost::get<SmallVector>(&mVariant))
        {
            return small->begin();
        }
        else
        {
            return &*boost::get<BigVector>(mVariant).begin();
        }
    }
    
    T* end()
    {
        if (auto small = boost::get<SmallVector>(&mVariant))
        {
            return small->end();
        }
        else
        {
            return &*boost::get<BigVector>(mVariant).end();
        }
    }
    
    std::size_t size() const
    {

        if (auto small = boost::get<SmallVector>(&mVariant))
        {
            return small->size();
        }
        else
        {
            return boost::get<BigVector>(mVariant).size();
        }
    }
    
    struct SmallVector
    {
        SmallVector() : mSize(), mArray() {}
        
        SmallVector(std::initializer_list<T> list) :
            mSize(list.size()),
            mArray(list)
        {
        }
        
        void push_back(T&& t)
        {
            mArray[mSize++] = std::move(t);
        }
        
        T* data() { return &mArray[0]; }
        T* begin() { return data(); }
        T* end() { return begin() + size(); }
        
        std::size_t size() const { return mSize; }
        
        constexpr std::size_t capacity() const { return SmallCapacity; }
        
        uint8_t mSize;
        std::array<T, SmallCapacity> mArray;
    };
    using BigVector = std::vector<T>;
    boost::variant<SmallVector, std::vector<T>> mVariant;
};


template<typename T, typename U, int SmallCapacity>
struct Map
{
    Map(std::initializer_list<std::pair<T, U>> list)
    {
        for (auto& pair : list)
        {
            //std::cout << "push back: " << pair.first << " " << pair.second << std::endl;
            mPair.first.push_back(std::move(pair.first));
            mPair.second.push_back(std::move(pair.second));
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
        
        iterator(FirstIt first, SecondIt second) : mPair(first, second)
        {
            //std::cout << "iterator " << *first << " " << *second << std::endl;
        }   
        
        Pair& operator*()
        {
            return mPair;
        }
        
        Pair* operator->()
        {
            return &mPair;
        }        
        
        bool operator==(const iterator& rhs) const
        {
            return mPair == rhs.mPair;
        }
        
        bool operator!=(const iterator& rhs) const
        {
            return mPair != rhs.mPair;
        }
        
        iterator& operator++()
        {
            ++mPair.first.it;
            ++mPair.second.it;
            return *this;
        }
        
        Pair mPair;
    };
    
    iterator begin()
    {
        return iterator(mPair.first.begin(), mPair.second.begin());
    }
    
    iterator end()
    {
        return iterator(mPair.first.end(), mPair.second.end());
    }    

    std::size_t size() const
    {
        return mPair.first.size();
    }

    
    std::pair<Vector<T, SmallCapacity>, Vector<U, SmallCapacity>> mPair;
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
