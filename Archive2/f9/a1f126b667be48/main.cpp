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

int main()
{
    srand(time(0));

    static const int count = 1000*1000;


    timespec ts;
    size_t startTime, endTime;
    
    clock_gettime(CLOCK_MONOTONIC, &ts);
    startTime = ts.tv_sec * 1000000000 + ts.tv_nsec;
    long long sum =0;


    for(int i =0; i<count; ++i)
    {
    int a = rand();
    sum+=a;
    {
        {
            {
                {{{{
        
        int b = rand();
        int a = rand();
        sum += a+b;
    }}}}
    }
    }
    }
    
    {
        int c = rand();
        int a = rand();
        sum += a+c;
    }
    
    } 
    

    clock_gettime(CLOCK_MONOTONIC, &ts);
    endTime = ts.tv_sec * 1000000000 + ts.tv_nsec;
    

    std::cout << "Scoped took " << (endTime - startTime) << " nanosec. "
              << "Each took " << (double(endTime - startTime)/(count/2)) << ". "
              << "(" << sum << ")"
              << std::endl;


    clock_gettime(CLOCK_MONOTONIC, &ts);
    startTime = ts.tv_sec * 1000000000 + ts.tv_nsec;
    sum =0;

    for(int i =0; i<count; ++i)
    {
    int a = rand();
    sum+=a;
    
        int b = rand();
        a = rand();
        sum += a+b;
    
        int c = rand();
        a = rand();
        sum += a+c;
    
    }
     
    clock_gettime(CLOCK_MONOTONIC, &ts);
    endTime = ts.tv_sec * 1000000000 + ts.tv_nsec;

    std::cout << "Unscoped took " << (endTime - startTime) << " nanosec. "
              << "Each took " << (double(endTime - startTime)/(count/2)) << ". "
              << "(" << sum << ")"
              << std::endl;

    return 0;
}
