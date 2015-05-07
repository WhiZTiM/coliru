#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::condition_variable cv;
std::mutex mtx;
 
void foo()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cv.notify_one();
}
 
int main()
{
    std::thread t;
    std::cout << "before starting, joinable: " << t.joinable() << '\n';
 
    t = std::thread(foo);
    std::cout << "after starting, joinable: " << t.joinable() << '\n';
    
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "before joining, joinable: " << t.joinable() << '\n';
 
    t.join();
    std::cout << "after joining, joinable: " << t.joinable() << '\n';
}