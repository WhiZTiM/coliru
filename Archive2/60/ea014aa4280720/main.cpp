#include <iostream>
#include <chrono>
#include <thread>
 
int main()
{
    using namespace std::literals;
    std::cout << "Hello waiter" << std::ene
 
 auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(50ms);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "Waited " << elapsed.count() << " ms\n";
}