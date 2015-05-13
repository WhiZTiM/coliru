#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>


struct Event
{
    Event(int n) : n(n) {}
    
    void handle()
    {
        std::cout << n << '\n';
    }
    
    int n;
};


struct A
{
    A() : thread([this]{ consumer_thread(); })
    {
    }
    
    ~A()
    {
        post(-1);
        thread.join();
    }
    
    A(const A&) = delete;
    A& operator=(const A&) = delete;
    
    void post(Event event)
    {
        bool notify = false;
        
        {
            std::lock_guard<std::mutex> lock(mutex);
            notify = events.empty();
            events.push_back(event);
        }
        
        if (notify)
        {
            condition.notify_one();            
        }
    }
    
    void consumer_thread()
    {
        for (;;)
        {
            {
                std::unique_lock<std::mutex> lock(mutex);
                while (events.empty())
                {
                    condition.wait(lock); // unlocks the mutex
                }
                std::swap(events, events2);
            }
            
            for (Event& event : events2)
            {
                if (event.n == -1)
                {
                    return;
                }
                event.handle();            
            }
            events2.clear();
        }
    }

    
    std::vector<Event> events;          char padding1[128 - sizeof(events)];
    std::mutex mutex;                   char padding2[128 - sizeof(mutex)];     // not sure if padding2 is needed
    std::condition_variable condition;  char padding3[128 - sizeof(condition)];    
    std::vector<Event> events2;         char padding4[128 - sizeof(events2)];    
    std::thread thread;
};


int main()
{
    {
        A a;
        std::atomic<bool> ready{false};
        std::thread t1([&a, &ready]{ while (!ready) {} for (int i = 0; i != 1000; ++i) { a.post(1000 + i); } });
        std::thread t2([&a, &ready]{ while (!ready) {} for (int i = 0; i != 1000; ++i) { a.post(2000 + i); } });
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ready = true;
        t1.join();
        t2.join();
    }
    std::cout << "End of program." << std::endl;
}

