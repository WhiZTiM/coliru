#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>

std::atomic<int> value(90000);

std::mutex output;

void loop(std::string name)
{
    int i;
    while((i = value.fetch_sub(1)) > 0)
        ;
    std::lock_guard<std::mutex> lock(output);
    if(i == 0)
        std::cout << name << " is a winner!\n";
    else
        std::cout << name << " lost :(\n";
}

int main()
{
    std::thread t1(loop, "loop1");
    std::thread t2(loop, "loop2");
    t1.join();
    t2.join();
}