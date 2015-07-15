#include <iostream>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

struct A
{
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
    int i;
    int j;
    int k;
    int l;
};


__attribute__((noinline))
//inline
bool bitwiseLessThan(const A& lhs, const A& rhs)
{
    return (lhs.a < rhs.a) |
           ( (!(rhs.a < lhs.a)) &
             ( (lhs.b < rhs.b) |
               ( (!(rhs.b < lhs.b)) &
                 ( (lhs.c < rhs.c) |
                   ( (!(rhs.c < lhs.c)) &
                     ( (lhs.d < rhs.d) ) ) ) ) ) );
}


__attribute__((noinline))
//inline
bool bitwiseEqual(const A& lhs, const A& rhs)
{
    return (lhs.a == rhs.a) & (lhs.b == rhs.b) & (lhs.c == rhs.c) & (lhs.d == rhs.d) &
            (lhs.e == rhs.e) & (lhs.f == rhs.f) & (lhs.g == rhs.g) & (lhs.h == rhs.h) &
    (lhs.i == rhs.i) & (lhs.j == rhs.j) & (lhs.k == rhs.k) & (lhs.l == rhs.l);
}



__attribute__((noinline))
//inline
bool logicalLessThan(const A& lhs, const A& rhs)
{
    return (lhs.a < rhs.a) ||
           ( (!(rhs.a < lhs.a)) &&
             ( (lhs.b < rhs.b) ||
               ( (!(rhs.b < lhs.b)) &&
                 ( (lhs.c < rhs.c) ||
                   ( (!(rhs.c < lhs.c)) &&
                     ( (lhs.d < rhs.d) ) ) ) ) ) );
}


__attribute__((noinline))
//inline
bool logicalEqual(const A& lhs, const A& rhs)
{
    return (lhs.a == rhs.a) && (lhs.b == rhs.b) && (lhs.c == rhs.c) && (lhs.d == rhs.d) &&
    (lhs.e == rhs.e) && (lhs.f == rhs.f) && (lhs.g == rhs.g) && (lhs.h == rhs.h) &&
    (lhs.i == rhs.i) && (lhs.j == rhs.j) && (lhs.k == rhs.k) && (lhs.l == rhs.l);
}


int main()
{
    srand(time(0));

    static const size_t COUNT = 20000000;
    A* values = new A[COUNT];
    for (size_t i = 0; i < COUNT; ++i)
    {
        values[i].a = rand()%2;
        values[i].b = rand()%2;
        values[i].c = rand()%2;
        values[i].d = rand()%2;
        values[i].e = rand()%2;
        values[i].f = rand()%2;
        values[i].g = rand()%2;
        values[i].h = rand()%2;
        values[i].i = rand()%2;
        values[i].j = rand()%2;
        values[i].k = rand()%2;
        values[i].l = rand()%2;


    }

    timespec ts;
    size_t startTime, endTime;
    size_t sum;

    sum = 0;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    startTime = ts.tv_sec * 1000000000 + ts.tv_nsec;

    for (size_t i = 0; i < COUNT; i+=2)
    {
        sum += bitwiseEqual(values[i], values[i+1]);
    }
    clock_gettime(CLOCK_MONOTONIC, &ts);
    endTime = ts.tv_sec * 1000000000 + ts.tv_nsec;

    std::cout << "Bitwise took " << (endTime - startTime) << " nanosec. "
              << "Each took " << (double(endTime - startTime)/(COUNT/2)) << ". "
              << "(" << sum << ")"
              << std::endl;


    sum = 0;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    startTime = ts.tv_sec * 1000000000 + ts.tv_nsec;

    for (size_t i = 0; i < COUNT; i+=2)
    {
        sum += logicalEqual(values[i], values[i+1]);
    }
    clock_gettime(CLOCK_MONOTONIC, &ts);
    endTime = ts.tv_sec * 1000000000 + ts.tv_nsec;

    std::cout << "Logical took " << (endTime - startTime) << " nanosec. "
              << "Each took " << (double(endTime - startTime)/(COUNT/2)) << ". "
              << "(" << sum << ")"
              << std::endl;

    return 0;
}
