#include <atomic>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <array>
#include <thread>


std::array<std::atomic<unsigned>, 100> atomics;
long padding[8];
std::atomic<bool> start{false};


using namespace std::chrono;
using Clock = high_resolution_clock;

void test(int index1, int index2)
{
    auto start_time = Clock::now();
    enum { num_iterations = 1000 * 1000 };
    
    std::thread t1([index1]{ while (!start) {} for (auto i = 0; i != num_iterations; ++i) atomics[index1]++; });
    std::thread t2([index2]{ while (!start) {} for (auto i = 0; i != num_iterations; ++i) atomics[index2]++; });
    start = true;
    t1.join();
    t2.join();
    auto elapsed = duration_cast<nanoseconds>(Clock::now() - start_time).count();
    std::cout << index1 << "-" << std::setw(2) << std::left << index2 << " distance=" << std::setw(3) << std::left << (((char*)&atomics[index2] - (char*)&atomics[index1])) << " time=" << (elapsed / num_iterations) << "ns/increment" << std::endl;
}


int main()
{
    test(0, 1);
    test(0, 2);
    test(0, 3);
    test(0, 4);
    test(0, 8);
    test(0, 12);
    test(0, 16);
    test(0, 24);
    test(0, 32);
    test(0, 48);
    test(0, 64);
    test(0, 96);
}

