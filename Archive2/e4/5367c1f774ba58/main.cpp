#include <iostream>
#include <mutex>
#include <thread>

std::mutex mx;

void print(char ch, int count)
{
    std::lock_guard<std::mutex> lock(mx);
    for (int i = 0; i < count; ++i)
    {
        std::cout << ch;
    }
    std::cout << std::endl;
}   
        
int main() {
     std::thread t1(print, 'x', 10);
     std::thread t2(print, '*',20);
     
     t1.join();
     t2.join();
     return 0;
}