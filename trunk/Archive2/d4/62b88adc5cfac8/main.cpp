#include <boost/function.hpp>
#include <functional>
#include <cstdlib>
#include <stdio.h>

#define TRACE printf("%s\n", __FUNCTION__);

__attribute__((noinline)) long test1(long a) { TRACE return boost::function<long()>([a]{ return a; })(); }
__attribute__((noinline)) long test2(long a, long b) { TRACE return boost::function<long()>([a, b]{ return a + b; })(); }
__attribute__((noinline)) long test3(long a, long b, long c) { TRACE return boost::function<long()>([a, b, c]{ return a + b + c; })(); }
__attribute__((noinline)) long test4(long a, long b, long c, long d) { TRACE return boost::function<long()>([a, b, c, d]{ return a + b + c + d; })(); }
__attribute__((noinline)) long test5(long a, long b, long c, long d, long e) { TRACE return boost::function<long()>([a, b, c, d, e]{ return a + b + c + d + e; })(); }


void* operator new(std::size_t n)
{
    printf("new %d\n", static_cast<int>(n));
    return malloc(n);
}


volatile int volly = 0;

int main()
{
    volly += test1(1);
    volly += test2(1, 2);
    volly += test3(1, 2, 3);
    volly += test4(1, 2, 3, 4);
    volly += test5(1, 2, 3, 4, 5);
    return volly;
}
