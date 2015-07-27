#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

void consumer(std::mutex& mtx, std::condition_variable& cv)
{
    using namespace std::literals;
    std::cout << "Sleeping for 3s...\n";
    std::this_thread::sleep_for(3s);
    
    std::cout << "Waiting 3s for signal signal...\n";
    std::unique_lock<std::mutex> latch(mtx);
    if (cv.wait_for(latch, 3s) == std::cv_status::timeout)
        std::cout << "timed out waiting for signal\n";
    else
        std::cout << "received signal!!!\n";
}

int main()
{
    std::mutex mtx;
    std::condition_variable cv;
    std::thread cthr(consumer, std::ref(mtx), std::ref(cv));
    cv.notify_one();
    cthr.join();
}