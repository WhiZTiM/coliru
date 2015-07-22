#include <iostream>
#include <new>

struct test1
{
    test1() { std::cout << __PRETTY_FUNCTION__ << ' ' << this << '\n'; }
    
    static void *operator new(std::size_t size)
    {
        std::cout << __PRETTY_FUNCTION__ << ' ' << size << '\n';
        return nullptr;
    }
    static void operator delete(void *p)
    {
        std::cout << __PRETTY_FUNCTION__ << ' ' << p << '\n';
    }
};

struct test2
{
    test2() { std::cout << __PRETTY_FUNCTION__ << ' ' << this << '\n'; }
    
    static void *operator new(std::size_t size)
    {
        std::cout << __PRETTY_FUNCTION__ << ' ' << size << '\n';
        throw std::bad_alloc();
    }
    static void operator delete(void *p)
    {
        std::cout << __PRETTY_FUNCTION__ << ' ' << p << '\n';
    }
};

struct test3
{
    test3() { std::cout << __PRETTY_FUNCTION__ << ' ' << this << '\n'; }
    
    static void *operator new(std::size_t size) throw()
    {
        std::cout << __PRETTY_FUNCTION__ << ' ' << size << '\n';
        return nullptr;
    }
    static void operator delete(void *p)
    {
        std::cout << __PRETTY_FUNCTION__ << ' ' << p << '\n';
    }
};

template<typename T>
void tester()
{
    std::cout << __PRETTY_FUNCTION__ << ' ' << '\n';
    try {
        auto t = new T();
        std::cout << "Allocated: " << t << '\n';
        delete t;
    } catch(std::exception const& e) {
        std::cout << "Caught: " << e.what() << "\n";
    }
    std::cout << "Done\n\n";
}

int main()
{
    tester<test1>();
    tester<test2>();
    tester<test3>();
}
