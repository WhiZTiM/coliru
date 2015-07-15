#include <boost/function.hpp>
#include <cstdlib>
#include <cstdio>
#include <iostream>


void* operator new(std::size_t n)
{
    std::printf("new %d\n", int(n));
    return std::malloc(n);
}


void* operator new[](std::size_t n)
{
    std::printf("new[] %d\n", int(n));
    return std::malloc(n);
}


int main()
{
    uint64_t a , b, c, d, e;
    boost::function<void()>([a]{}); // 8
    boost::function<void()>([a, b]{}); // 16
    boost::function<void()>([a, b, c]{}); // 24
    boost::function<void()>([a, b, c, d]{}); // 32
    boost::function<void()>([a, b, c, d, e]{}); // 40
}
