#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <cstdio>

#define AVC_INFO_NOOID(FMT, ...) \
    vprintf(FMT, __VA_ARGS__)

#define LOG_ELAPSED_TIME(TIMER, OPERATION_FORMAT, ...) \
    AVC_INFO_NOOID(OPERATION_FORMAT " took %f milliseconds", __VA_ARGS__, TIMER.count()) 
 
int main()
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    std::cout << "24 hours ago, the time was "
              << std::put_time(std::localtime(&now_c), "%F %T") << '\n';
 
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::cout << "Hello World\n";
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Printing took "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << "us.\n";
              
    std::chrono::duration_cast<std::chrono::microseconds> t = (end - start);
    
    LOG_ELAPSED_TIME(t, "This %s", "thing");
}