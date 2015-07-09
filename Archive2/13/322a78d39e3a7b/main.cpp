// condition_variable::wait (with predicate)
#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <atomic>

std::atomic<int> cargo;
void consume ()
{
    while(1)
    {

        int cur_cargo;
        while(! (cur_cargo = cargo.load(std::memory_order_relaxed))); // spin until cargo is not 0

        std::cout << cur_cargo << '\n';
        
        if(cur_cargo == 100) // needed or else this program would never terminate (consumer thread would run infinitely and .join() would block infinitely)
                             // typical use may be a "done flag", but this suffices for this example
            break;
            
        cargo.store(0,std::memory_order_relaxed);
        
       
    }
}

int main ()
{
    std::thread consumer_thread (consume);

    int i=0;
    while(1)
    {
        while(cargo.load(std::memory_order_relaxed)); // spin until cargo is 0
        cargo.store(i++,std::memory_order_relaxed);

        if(i > 100)
        {
            break;
        }
    }

    consumer_thread.join();

    return 0;
}