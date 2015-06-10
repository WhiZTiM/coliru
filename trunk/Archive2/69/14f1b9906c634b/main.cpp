#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <array>
#include <cassert>
#include <vector>
#include <iostream>




template<typename T>
struct Vector
{
    enum { SmallCapacity = 2 };
    
    Vector() : variant_(SmallVector()) {}

    Vector(std::size_t size) : variant_(size <= SmallCapacity ? Variant(SmallVector(size)) : Variant(BigVector(size)))
    {
    }

    Vector(std::initializer_list<T> list) :
        variant_(list.size() <= SmallCapacity ? SmallVector(list) : std::vector<T>(list))
    {
    }

    template<typename InputIterator>
    Vector(InputIterator b, InputIterator e)
    {
        auto length = e - b;
        if (length >= SmallCapacity)
        {
            variant_ = BigVector(b,e );
        }
        else
        {

            SmallVector small;
            for (auto i = b; i != e; ++i)
            {
                small.push_back(*i);
            }
            variant_ = std::move(small);
        }
    }

    using const_iterator = const T*;
    using iterator = T*;

    const T& at(std::size_t i) const
    {
        if (i >= size())
        {
            throw std::out_of_range("Vector");
        }
        return data()[i];
    }

    T& at(std::size_t i)
    {
        return const_cast<T&>(static_cast<const Vector&>(*this).at(i));
    }

    const T& operator[](std::size_t i) const
    {
        return at(i);
    }

    T& operator[](std::size_t i)
    {
        return at(i);
    }

    T& front()
    {
        return at(0);
    }

    const T& front() const
    {
        return at(0);
    }

    T& back()
    {
        return at(size() - 1);
    }

    const T& back() const
    {
        return at(size() - 1);
    }

    template<typename InputIterator>
    void assign(InputIterator b, InputIterator e)
    {
        auto length = e - b;

        if (auto small = getSmall())
        {
            if (length < SmallCapacity)
            {
                small->clear();
                for (auto i = b; i != e; ++i)
                {
                    small->push_back(*i);
                }
            }
            else
            {
                variant_ = BigVector(b, e);
            }
        }
        else
        {
            getBig().assign(b, e);
        }
    }

    void clear()
    {
        if (auto small = getSmall())
        {
            small->clear();
        }
        else
        {
            getBig().clear();
        }
    }

    void push_back(T&& t)
    {
        if (auto small = getSmall())
        {
            if (small->size() < small->capacity())
            {
                small->push_back(std::move(t));
            }
            else
            {
                BigVector big;
                big.reserve(2 * small->capacity());
                for (auto i = small->begin(), e = small->end(); i != e; ++i)
                {
                    big.push_back(std::move(*i));
                }
                big.push_back(std::move(t));
                variant_ = std::move(big);
                return;
            }
        }
        else
        {
            auto& big = getBig();
            big.push_back(std::move(t));
        }
    }

    void push_back(const T& t)
    {
        push_back(T(t));
    }

    const T* data() const
    {
        if (auto small = getSmall()) return small->data();
        return &*getBig().data();
    }

    const T* begin() const
    {
        if (auto small = getSmall()) return small->begin();
        return &*getBig().begin();
    }

    const T* end() const
    {
        if (auto small = getSmall()) return small->end();
        return &*getBig().end();
    }

    T* begin()
    {
        if (auto small = getSmall()) return small->begin();
        return &*getBig().begin();
    }

    T* end()
    {
        if (auto small = getSmall()) return small->end();
        return &*getBig().end();
    }

    std::size_t capacity() const
    {
        if (auto small = getSmall()) return small->capacity();
        return getBig().capacity();
    }

    std::size_t size() const
    {
        if (auto small = getSmall()) return small->size();
        return getBig().size();
    }

    bool empty() const
    {
        if (auto small = getSmall()) return small->empty();
        return getBig().empty();
    }

    void reserve(std::size_t n)
    {
        if (n < SmallCapacity)
        {
            return;
        }

        if (auto small = getSmall())
        {
            BigVector big;
            big.reserve(n);
            big.assign(small->begin(), small->end());
            variant_ = std::move(big);
        }
        else
        {
            getBig().reserve(n);
        }
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

        void push_back(const T& t)
        {
            assert(size_ < SmallCapacity);
            array_[size_++] = t;
        }

        void push_back(T&& t)
        {
            assert(size_ < SmallCapacity);
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

        bool empty() const
        {
            return size_ == 0;
        }

        std::size_t size() const { return size_; }

        std::size_t capacity() const { return SmallCapacity; }

        void clear()
        {
            for (auto i = 0 * size(); i != size(); ++i)
            {
                array_[i].~T();
            }

            size_ = 0;
        }

        uint8_t size_;
        std::array<T, SmallCapacity> array_;
    };

    using BigVector = std::vector<T>;
    using Variant = boost::variant<SmallVector, std::vector<T>>;

    const SmallVector* getSmall() const { return boost::get<SmallVector>(&variant_); }
    const BigVector& getBig() const { return boost::get<BigVector>(variant_); }

    SmallVector* getSmall() { return boost::get<SmallVector>(&variant_); }
    BigVector& getBig() { return boost::get<BigVector>(variant_); }

    boost::variant<SmallVector, std::vector<T>> variant_;
};


template<typename T, typename U>
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
        using FirstIt = typename Vector<T>::iterator;
        using SecondIt = typename Vector<U>::iterator;
        
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

    
    std::pair<Vector<T>, Vector<U>> mPair;
};



int main()
{
    Vector<int> vec;
    for (int i = 0; i != 20; ++i)
    {
        std::cout << i << ' ' << std::flush;
        vec.push_back(i);        
        std::cout << "\t";
        for (auto i : vec) std::cout << i << ' ';
        std::cout << std::endl;
    }
    
    Map<int, int> map = {
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
