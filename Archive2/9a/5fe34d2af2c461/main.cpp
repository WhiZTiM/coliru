#include <cstdint>
#include <iostream>
#include <thread>


struct rdtsc_clock
{
    using time_point = std::uint64_t;
    
    static time_point now()
    {
        std::uint32_t hi, lo;
        __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
        return (static_cast<time_point>(hi) << 32) | static_cast<time_point>(lo);
    }
};


using Clock = rdtsc_clock;


int main()
{
    auto high_t1 = std::chrono::high_resolution_clock::now();
    auto low_t1 = Clock::now();
    std::this_thread::sleep_until(high_t1 + std::chrono::seconds(1));
    auto low_t2 = Clock::now();
    auto high_t2 = std::chrono::high_resolution_clock::now();
    
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(high_t2 - high_t1).count() << std::endl;
    std::cout << low_t2 - low_t1 << std::endl;
}
