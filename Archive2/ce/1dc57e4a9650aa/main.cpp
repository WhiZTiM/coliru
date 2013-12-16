#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
 
std::mutex m;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;
 
void worker_thread()
{
    // Wait until main() sends data
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return ready;});
    }
 
    std::cout << "Worker thread is processing data\n";
    data += " after processing";
 
    // Send data back to main()
    {
        std::lock_guard<std::mutex> lk(m);
        processed = true;
        std::cout << "Worker thread signals data processing completed\n";
    }
    cv.notify_one();
}
 
int main()
{
    std::thread worker(worker_thread);
    
    cv.notify_one();//nothing to do
    data = "Example data";
    // send data to the worker thread
    {
        std::lock_guard<std::mutex> lk(m);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    cv.notify_one();
 
    // wait for the worker
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, []{return processed;});
    }
    std::cout << "Back in main(), data = " << data << '\n';
 
    worker.join();
}