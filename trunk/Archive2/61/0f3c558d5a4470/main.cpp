#include <time.h>
#include <chrono>
#include <pthread.h>
#include <stdio.h>

using namespace std::chrono;
 
typedef unsigned long long uint64;
const uint64 ITERATIONS = 5LL * 1000LL * 1000LL;
 
volatile uint64 s1 = 0;
volatile uint64 s2 = 0;
 
void* run(void*)
{
    uint64 value = s2;
    while (true)
    {
        while (value == s1)
        {
            // busy spin
        }
        value = __sync_add_and_fetch(&s2, 1);
    }
}
 
int main ()
{
    pthread_t threads[1];
    pthread_create(&threads[0], NULL, run, NULL);
 
    auto start_time = steady_clock::now();
 
    uint64 value = s1;
    while (s1 < ITERATIONS)
    {
        while (s2 != value)
        {
            // busy spin
        }
        value = __sync_add_and_fetch(&s1, 1);
    }
 
    uint64 duration = duration_cast<nanoseconds>(steady_clock::now() - start_time).count();
 
    printf("duration = %lld\n", duration);
    printf("ns per op = %lld\n", (duration / (ITERATIONS * 2)));
    printf("op/sec = %lld\n",  
        ((ITERATIONS * 2L * 1000L * 1000L * 1000L) / duration));
    printf("s1 = %lld, s2 = %lld\n", s1, s2);
 
    return 0;
}
