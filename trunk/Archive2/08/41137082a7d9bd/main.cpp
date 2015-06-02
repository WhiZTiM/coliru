#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>
#include <chrono>
    
class foo {
  
    std::thread t_;
    std::atomic_flag quit_;
    
    std::atomic_bool started_;
  
public:

    foo() 
    : started_{false}
    {
        quit_.test_and_set();
        t_ = std::thread{&foo::thread_func,this};
        while (!started_.load());
    }
    
    void thread_func() 
    {
        std::once_flag of_;
        while (quit_.test_and_set()) {
            std::call_once(of_,[this](){ started_.store(true); std::cout << "started\n"; });
            std::cout << "bleet\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
  
    ~foo() {
        quit_.clear();        
        t_.join();        
    }  
};

  
int main() { 
    foo f;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}