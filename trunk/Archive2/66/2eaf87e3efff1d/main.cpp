#include <iostream>
#include <thread>
#include <chrono>

void foo()
{
    for (auto i = 0; i < 1000; ++i)
        std::cout << i << std::endl;
}

int main()
{
    std::thread t1(&foo);
    
    if(t1.joinable())
        t1.join();
    else
        t1.detach();
    
    return 0;
}