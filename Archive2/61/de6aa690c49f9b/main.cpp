#include <array>
#include <cstdint>
#include <new>


using T = int;


std::array<typename std::aligned_storage<sizeof(T), alignof(T)>::type, 256> data;
uint8_t begin_;
uint8_t end_;


void pop_front()
{
    static_cast<T*>(static_cast<void*>(&data[begin_++ % 256]))->~T();
}

void push_back(T t)
{
    new (&data[end_++ % 256]) T(t);
}

T& front()
{
    return *static_cast<T*>(static_cast<void*>(&data[begin_ % 256]));
}

T& back()
{
    return *static_cast<T*>(static_cast<void*>(&data[end_ % 256]));
}

int size()
{
    return end_ - begin_;
}

T* begin()
{
    return static_cast<T*>(static_cast<void*>(&data[begin_ % 256]));
}

T* end()
{
    return begin() + size();
}


#include <iostream>
#include <iomanip>


void print()
{
    for (auto i = begin(), e = end(); i != e; ++i)
    {
        std::cout << std::setw(2) << std::right << *i << ' ';;
    }
    std::cout << '\n';
}


int main()
{
    for (int i = 0; i != 99; ++i)
    {
        push_back(i);
        print();
    }
    
    for (int i = 0; i != 99; ++i)
    {
        pop_front();
        print();
    }
}


