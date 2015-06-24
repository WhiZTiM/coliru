#include <atomic>
#include <iostream>
#include <thread>


enum { num_iterations = 10 * 1000 * 1000 };


using Clock = std::chrono::high_resolution_clock;
using Counter = std::atomic<long>;

Counter x{0};
char padding[128];
Counter y{0};

void test(Counter& a, Counter& b)
{
    for (;;)
    {        
        // fetch a local copy 
        auto b_copy = b++;
        if (b_copy == num_iterations) break;
        while (a < b_copy);
    }
}


int main()
{   
    std::thread t1([]{ test(x, y); });
    auto start_time = std::chrono::high_resolution_clock::now();
    test(y, x);
    t1.join();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - start_time).count();
    std::cout << "x=" << x << " y=" << y << " latency=" << int(0.5 + 1.0 * elapsed_ns / (num_iterations * 2)) << std::endl;
    
}

