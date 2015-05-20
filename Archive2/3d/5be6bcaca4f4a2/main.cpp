#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>


std::atomic<long> atomic_counter{0};


int main()
{
    enum { num_iterations = 50 * 1000 * 1000 };
    using Clock = std::chrono::high_resolution_clock;
    auto start_time = Clock::now();
    std::thread t1([]{ for (auto i = 0ul; i != num_iterations; ++i) { atomic_counter++; } });
    t1.join();


    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - start_time).count();
    std::cout
		<< " increment=" << int(0.5 + 1.0 * elapsed_ns / num_iterations) << "ns"
		<< std::endl;
}
