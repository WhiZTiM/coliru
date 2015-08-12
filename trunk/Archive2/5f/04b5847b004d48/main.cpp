#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <exception>


int main() {
    
    std::promise<void> prom;
    
    std::future<void> fut = prom.get_future();
    
    std::thread{[](std::promise<void> prom){ 
                    try { 
                            throw 0;
                            
                            prom.set_value_at_thread_exit(); 
                        } catch(...){ 
                            prom.set_exception_at_thread_exit( std::current_exception()); 
                        }                      
                    }, std::move(prom)}.detach();
    
    
    try {
        fut.get();
    } catch(...) {
        std::cout << "exception caught"; 
    }
}

