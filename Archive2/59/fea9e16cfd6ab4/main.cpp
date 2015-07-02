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
};

inline
bool bitwiseLessThan(A lhs, A rhs)
{
    return (lhs.a < rhs.a) |
           ( (!(rhs.a < lhs.a)) &
             ( (lhs.b < rhs.b) |
               ( (!(rhs.b < lhs.b)) &
                 ( (lhs.c < rhs.c) |
                   ( (!(rhs.c < lhs.c)) &
                     ( (lhs.d < rhs.d) ) ) ) ) ) );
}

inline
bool logicalLessThan(A lhs, A rhs)
{
    return (lhs.a < rhs.a) ||
           ( (!(rhs.a < lhs.a)) &&
             ( (lhs.b < rhs.b) ||
               ( (!(rhs.b < lhs.b)) &&
                 ( (lhs.c < rhs.c) ||
                   ( (!(rhs.c < lhs.c)) &&
                     ( (lhs.d < rhs.d) ) ) ) ) ) );
}

int main()
{
    srand(time(0));

    static const size_t COUNT = 20000000;
    A* values = new A[COUNT];
    for (size_t i = 0; i < COUNT; ++i)
    {
        values[i].a = rand();
        values[i].b = rand();
        values[i].c = rand();
        values[i].d = rand();
    }

    timespec ts;
    size_t startTime, endTime;
    size_t sum;

    sum = 0;

    clock_gettime(CLOCK_MONOTONIC, &ts);
    startTime = ts.tv_sec * 1000000000 + ts.tv_nsec;

    for (size_t i = 0; i < COUNT; i+=2)
    {
        sum += bitwiseLessThan(values[i], values[i+1]);
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
        sum += logicalLessThan(values[i], values[i+1]);
    }
    clock_gettime(CLOCK_MONOTONIC, &ts);
    endTime = ts.tv_sec * 1000000000 + ts.tv_nsec;

    std::cout << "Logical took " << (endTime - startTime) << " nanosec. "
              << "Each took " << (double(endTime - startTime)/(COUNT/2)) << ". "
              << "(" << sum << ")"
              << std::endl;

    return 0;
}
