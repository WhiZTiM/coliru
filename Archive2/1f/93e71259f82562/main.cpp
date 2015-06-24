#include <atomic>
#include <iostream>
#include <thread>


enum { num_iterations = 20 * 1000 * 1000 };


using Clock = std::chrono::high_resolution_clock;
using Counter = std::atomic<long>;

// use padding to prevent false sharing
__attribute__((aligned(128))) Counter x{0};
__attribute__((aligned(128))) Counter y{0};


void test(Counter& a, Counter& b)
{
    for (;;)
    {        
        // fetch once
        long b_incremented = ++b;
        if (b_incremented == num_iterations) break;

        // compare against local copy
        while (a < b_incremented);
    }
}


int main()
{   
    auto start_time = std::chrono::high_resolution_clock::now();
    std::thread t1([]{ test(x, y); }); // overhead of thread startup and shutdown can be diluted by increasing num_iterations. 
    test(y, x);
    t1.join();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - start_time).count();
    std::cout << "x=" << x << " y=" << y << " average cost of notifying change to another core: " <<  1.0 * elapsed_time / (2 * num_iterations) << '\n';
}

