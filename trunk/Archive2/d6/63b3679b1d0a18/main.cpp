#include <iostream>
#include <condition_variable>
#include <thread>
#include <array>
#include <chrono>
 
 
std::condition_variable cv;
std::mutex m1;
std::mutex m2;
std::mutex m3;
 

std::thread t1([]{
    std::unique_lock<std::mutex> l1(m1);        
    std::cout << "t1 is waiting" << std::endl;        
    cv.wait(l1); // (mutex is unlocked during wait)        
    std::cout << "t1 woke up" << std::endl;
});


std::thread t2([]{
    std::unique_lock<std::mutex> l2(m2);        
    std::cout << "t2 is waiting" << std::endl;        
    cv.wait(l2);        
    std::cout << "t2 woke up" << std::endl;
});


std::thread t3([]{
    std::unique_lock<std::mutex> l3(m3);        
    std::cout << "t3 is waiting" << std::endl;        
    cv.wait(l3);        
    std::cout << "t3 woke up" << std::endl;
});


int main()
{    
    // wait till all threads have started
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    std::cout << "notify_all 1" << std::endl;
    cv.notify_all();
    
    std::cout << "notify_all 2" << std::endl;
    cv.notify_all();
    
    std::cout << "notify_all 3" << std::endl;
    cv.notify_all();
    
    t3.join();
    t2.join();
    t1.join();
}
