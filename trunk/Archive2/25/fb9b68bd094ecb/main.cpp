#include <iostream>
#include <algorithm>

#include <cstdlib>

template< std::size_t argument, std::size_t base = 2, bool = (argument < base) >
constexpr std::size_t log = 1 + log< (argument / base), base >;
 
template< std::size_t argument, std::size_t base >
constexpr std::size_t log< argument, base, true > = 0;

template< typename ...types >
struct alignas(2 << std::max({log< sizeof(types) - 1 >...})) aligned_storage
{

};

struct A
{
    int j;
    A(int i) : j(i) { std::cout << j << ' ' << __PRETTY_FUNCTION__ << std::endl; }
    ~A() { std::cout << j << ' ' << __PRETTY_FUNCTION__ << std::endl; } 
};

struct B
{
    short j;
    B(short i) : j(i) { std::cout << j << ' ' << __PRETTY_FUNCTION__ << std::endl; }
    ~B() { std::cout << j << ' ' << __PRETTY_FUNCTION__ << std::endl; } 
};

int
main()
{
    aligned_storage< A, B > storage;
    auto a = ::new (&storage) A{1};
    a->~A();
    auto b = ::new (&storage) B{2};
    b->~B();
    return EXIT_SUCCESS;
}
