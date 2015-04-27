#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

using namespace std;

std::mutex globalMutex;   // Global is bad!  ;)

void call_from_thread(int thread_id)
{
//    globalMutex.lock();
    std::lock_guard<std::mutex> guard(globalMutex);
    cout << "Thread [" << thread_id << "] launched." << endl;
//    globalMutex.unlock();
}

int main()
{
    unsigned int nr_threads  = {6};
    
    auto threads = std::vector<std::thread>();

    for(unsigned int i =0; i<nr_threads; ++i)
    {
        threads.push_back(std::thread(call_from_thread, i));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }
    
    return 0;
}

