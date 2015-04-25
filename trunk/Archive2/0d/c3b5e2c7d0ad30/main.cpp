#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex print_mutex;

void function1()
{
    std::cout << "Thread1 started" << std::endl;

    while (true)
    {
        for (size_t i = 0; i<= 1000000000; i++)
            continue;
        std::unique_lock<std::mutex> lock(print_mutex);        
        std::cout << "This is function1" << std::endl;
        lock.unlock();
    }
}

void function2()
{
    std::cout << "Thread2 started" << std::endl;
    while (true)
    {
        for (size_t i = 0; i <= 1000000000; i++)
            continue;
        std::unique_lock<std::mutex> lock(print_mutex);       
        std::cout << "This is function2" << std::endl;
        lock.unlock();
    }
}

int main()
{
    std::thread t1(function1);
    std::thread t2(function2);

    t1.join();
    t2.join();

    return 0;
}