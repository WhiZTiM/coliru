#include <chrono>
#include <iostream>
#include <thread>
#include <unistd.h>


using Clock = std::chrono::high_resolution_clock;


Clock::time_point sleep_until(Clock::time_point current_time, Clock::time_point wakeup_time)
{
    while (wakeup_time - current_time > std::chrono::milliseconds(1))
    {
        std::this_thread::sleep_for((wakeup_time - current_time) / 2);   
        current_time = Clock::now();
        
    }
    
    while (wakeup_time - current_time > std::chrono::microseconds(500))
    {
        usleep(1);
        current_time = Clock::now();
    }
    
    while (wakeup_time - current_time > std::chrono::microseconds(20))
    {
        sched_yield();
        current_time = Clock::now();
    }
    
    while (wakeup_time > current_time)
    {
        current_time = Clock::now();
    }
    
    return current_time;
    
}



int main()
{
    auto now = Clock::now();
    auto start_time = now;
    auto should_wakeup_time = now + std::chrono::milliseconds(1);
    auto actual_wakeup_time = sleep_until(now, should_wakeup_time);
    auto time_slept = std::chrono::duration_cast<std::chrono::nanoseconds>(actual_wakeup_time - start_time).count();
    auto error = std::chrono::duration_cast<std::chrono::nanoseconds>(actual_wakeup_time - should_wakeup_time).count();
    std::cout << "Woke up after " << time_slept << " nanoseconds. This is " << error << " ns too late";;
}



