#include <iostream>
#include <sstream>
#include <exception>

class scoped_heap_overflow_exception final : public std::exception
{
public:
    scoped_heap_overflow_exception(std::size_t size) : size(size)
    {}
    
    virtual char const * what() const noexcept
    {
        std::stringstream ss;
        ss << "temp_heap with heap " << size << " would exceed, allocated memory";
        return ss.str().c_str();
    }
private:
    std::size_t size;
};

template<std::size_t Size>
class scoped_heap final
{
public:
    scoped_heap() : current(heap) {}
    
    std::size_t free_bytes()
    {
        return heap + Size - current;
    }
    
    template<
        typename T,
        typename ...Args>
    T * alloc(Args && ...args)
    {
        if (current + sizeof(T) > heap + Size) throw scoped_heap_overflow_exception(Size);
        T* p = (T*)current;
        *p = T(std::forward<Args>(args)...);
        current += sizeof(T);
        return p;
    }
private:
    char heap[Size];
    char * current;
};

int main()
{
    scoped_heap<sizeof(int) * 2 / sizeof(char)> heap;
    std::cout << "available bytes: " << heap.free_bytes() << std::endl;
    int * x = heap.alloc<int>(2);
    std::cout << "value of x(int): " << *x << std::endl;
    std::cout << "available bytes: " << heap.free_bytes() << std::endl;
    float * y = heap.alloc<float>(2.5f);
    std::cout << "value of y(float): " << *y << std::endl;
    std::cout << "available bytes: " << heap.free_bytes() << std::endl;
}