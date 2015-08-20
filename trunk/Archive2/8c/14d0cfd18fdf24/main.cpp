#include <iostream>
#include <future>
#include <thread>
#include <chrono>
 
int main()
{
    std::future<int> future = std::async(std::launch::async, [](){ 
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        return 8;  
    }); 
 
    std::cout << "waiting...\n";
    std::future_status status;
    
        status = future.wait_for(std::chrono::milliseconds::max());
        if (status == std::future_status::deferred) {
            std::cout << "deferred\n";
        } else if (status == std::future_status::timeout) {
            std::cout << "timeout\n";
        } else if (status == std::future_status::ready) {
            std::cout << "ready!\n";
        }
 
    std::cout << "result is " << future.get() << '\n';
}