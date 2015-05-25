#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>



void func(std::atomic_int& i) {
    int t = i.load(std::memory_order_acquire);
    
    std::cout << "starting\n";
    while (t == i.load(std::memory_order_acquire)) {
        
    }
    std::cout << "done\n"; 
}


int main()
{
    std::atomic_int i{};    
    std::thread t{&func,std::ref(i)};    
    std::this_thread::sleep_for(std::chrono::seconds(1));    
    std::cout << "sending\n"; 
    i.store(1, std::memory_order_release);
    std::cout << "sent\n"; 
    t.join();
}