#include <iostream>
#include <future>
#include <thread>
#include <chrono>
 
 int Task(int count)
 {
     int i = 0;
     while(i < count){
         std::this_thread::sleep_for(std::chrono::seconds(1));
         i++;
     }
     return i;
 }
 
int main()
{
    // future from a packaged_task
    std::future<int> fut;
    
    std::cout << "Future Valid: " <<fut.valid()<<"\n";
    
    fut = std::async(Task,3);
    std::cout << "valid Future: " << fut.valid() << " waiting ";
    while(fut.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready)
        std::cout << ".";
    std::cout <<"\n";
    int g = fut.get();
    std::cout << "Done:" << g << "\n";
}