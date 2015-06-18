#include <iostream>
#include <thread>
#include <utility>
#include <mutex>


struct boo {

    std::mutex mutex;
    
    void foo() {     
        std::unique_lock<std::mutex> lock{mutex};
        std::cout << std::this_thread::get_id() << " starting..\n";     
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << std::this_thread::get_id() << " stopping..\n";     
    }
  
};



int main() {
    
    boo b;
    
    std::thread p{&boo::foo,&b};
    std::thread q{&boo::foo,&b};
    std::thread r{&boo::foo,&b};
    
    p.join();
    q.join();
    r.join();    
}