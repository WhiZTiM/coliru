#include <iostream>
#include <chrono>
#include <thread>

 
int main() 
{
     auto child = std::thread([] { 
            std::chrono::seconds delay(5); 
            std::this_thread::sleep_for(delay); 
            std::cout << "child exit" << std::endl; 
            exit(0);  
        }); 

    child.detach();
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::cout << "Main exit" << std::endl;
}