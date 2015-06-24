#include <atomic>
#include <iostream>
#include <thread>


enum { num_iterations = 100 * 1000 };


std::atomic<int> threads_running{0};

volatile long x = 0;
volatile long y = 0;


void test(volatile long& a, volatile long& b)
{
    threads_running++;
    
    for (;;)
    {        
        if (++b == num_iterations) break;
        while (a < b);
    }
    
    threads_running--;
}


int main()
{
    
    std::thread([]{
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "Timeout. x=" << x << " y=" << y << std::endl;
        std::abort();
    }).detach();
    
    std::thread t1([]{ test(x, y); });
    std::thread t2([]{ test(y, x); });
    
    while (threads_running != 2);
    auto start_time = std::chrono::high_resolution_clock::now();
    while (threads_running != 0);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    std::cout << "elapsed_ns=" << elapsed_ns << " / " << num_iterations << " = " << int(0.5 + 1.0 * elapsed_ns / num_iterations) << std::endl;
    
    t1.join();
    t2.join();
   
}


