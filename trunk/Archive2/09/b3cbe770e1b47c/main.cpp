#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <shared_mutex>

struct{
    int a,b,c;
}data;

std::shared_timed_mutex lockingMutex;
 
void read_thread(int n)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(25*n));
    int i=3;
    while(i-->0)
    {
        lockingMutex.lock_shared();
        std::cout << "[" << n << "] a: " << data.a << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "[" << n << "] b: " << data.b << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "[" << n << "] c: " << data.c << std::endl;
        lockingMutex.unlock_shared();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void write_thread()
{
    int i=3;
    while(i-->0)
    {
        lockingMutex.lock();
        std::cout << "Wrinting" << std::endl;
        data.a++; data.b++; data.c++;
        lockingMutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
 
int main() 
{
    std::thread t1(read_thread, 1);
    std::thread t2(read_thread, 2);
    std::thread t3(read_thread, 3);
    std::thread t4(write_thread);
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}