#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>


using namespace std::chrono;
using Clock = high_resolution_clock;

int main(int, char** argv)
{
    #ifdef ATOMIC
    std::atomic<unsigned> i{0};
    #else
    unsigned i = 0;
    #endif
    
    auto start_time = Clock::now();
    enum { num_iterations = 10000 };
    while (i++ != num_iterations)  {}
    
    auto elapsed = duration_cast<nanoseconds>(Clock::now() - start_time).count();
    std::cout << argv[0] << ": " << (elapsed / num_iterations) << "ns" << std::endl;
}

