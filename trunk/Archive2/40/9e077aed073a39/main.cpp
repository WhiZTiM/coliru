#include <iostream>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>


std::mutex m;
std::condition_variable v;

void test_wait_until(int ms)
{
    std::unique_lock<std::mutex> lock(m);

    std::cout << ms << "ms start\n";
    auto expires = std::chrono::system_clock::now() + std::chrono::milliseconds(ms);
    bool run = true;

    do
    {
        // This loop will run at 100% cpu time until
        // the timeout expires.

        auto status = v.wait_until(lock, expires);

        if(status == std::cv_status::timeout){
            std::cout << ms << "ms expired\n";
            run=false;
        }

        if(status == std::cv_status::no_timeout){
            // If the commend below is removed the
            // termial will be filled by the printout.
            // until the timeout expires.

            std::cout << ms << "ms did not expire\n";
        }
    }while(run);
}


int main()
{
    test_wait_until( -100);
}