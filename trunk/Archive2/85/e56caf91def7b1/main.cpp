#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>



std::mutex print_mutex;
std::atomic_bool flag(true);
void function1()
{
    std::cout << "Thread1 started" << std::endl;

    while (true)
    {
        while(!flag);        
        std::cout << "This is function1" << std::endl;
        flag = false;
    }
}

void function2()
{
    std::cout << "Thread2 started" << std::endl;
    while (true)
    {
        while(flag);        
        std::cout << "This is function2" << std::endl;
        flag = true;
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