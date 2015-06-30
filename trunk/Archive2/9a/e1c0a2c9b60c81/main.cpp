#include <thread>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

int main()
{
    std::thread t([] () {});
    t.join();
    return 0;
}