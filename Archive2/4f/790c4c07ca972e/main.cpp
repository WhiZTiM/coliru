#include <thread>
#include <iostream>
#include <atomic>
#include <chrono>


std::atomic<uint64_t> n[10];


int main()
{
    std::thread([]{ while (++n[0]); }).detach();
    std::thread([]{ while (++n[1]); }).detach();
    std::thread([]{ while (++n[9]); }).detach();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto n0 = n[0].load();
    auto n1 = n[1].load();
    auto n9 = n[9].load();
    std::cout
        << n0 << '\n'
        << n1 << '\n'
        << n9 << '\n';
}
