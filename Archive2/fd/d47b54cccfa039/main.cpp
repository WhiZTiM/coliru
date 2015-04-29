#include <atomic>
#include <thread>
#include <iostream>
#include <chrono>


struct blah {
    std::atomic_flag quitflag_;
    
    blah() { quitflag_.test_and_set(); }
    
    void request_quit() { std::cout << "quitting.."; quitflag_.clear(); }
    
    void run() {
     
        while (quitflag_.test_and_set()) {
            std::cout << "still here..";
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
};


void foo(blah& b) {
    std::this_thread::sleep_for(std::chrono::seconds(6));
    b.request_quit();
}


int main() {
    
    blah b;
    
    std::thread t{&foo,std::ref(b)};
    
    b.run();
        
    
    t.join();    
}