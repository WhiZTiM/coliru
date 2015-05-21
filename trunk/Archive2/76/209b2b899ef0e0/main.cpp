#include "tbb/concurrent_queue.h"
#include <atomic>
#include <condition_variable>
#include <cstring>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>


unsigned long volatile g;
char padding[128];
std::atomic<int> counter{0};



enum { max_queue_size = 100 };


struct Event
{
    Event(int n = 0) : n(n) {}

    void handle()
    {
        counter++;
        // do some work
        for (int i = 0; i != 100; ++i)
        {
            g += g; // volatile access is unoptimizable 
        }
    }

    volatile int n;
};


#ifdef ATOMIC // tbb::concurrent_bounded_queue makes use of atomic operations and is mostly lockfree
struct Queue
{
    Queue() : mThread([this]{ consumer_thread(); })
    {
        mQueue.set_capacity(max_queue_size);
    }

    ~Queue()
    {
        mQueue.push(-1);
        mThread.join();
    }

    void post(Event event)
    {
        mQueue.push(event);
    }

    void consumer_thread()
    {
        for (;;)
        {
            Event event;
            mQueue.pop(event);
            if (event.n == -1)
            {
                return;
            }
            event.handle();
        }
    }

    tbb::concurrent_bounded_queue<Event> mQueue;
    std::thread mThread;
};
#else


struct Queue
{
    Queue() : thread([this]{ consumer_thread(); })
    {
        events.reserve(max_queue_size);
        events2.reserve(max_queue_size);
    }

    ~Queue()
    {
        post(-1);
        thread.join();
    }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void post(Event event)
    {
        bool was_empty = false;

        {
            std::unique_lock<std::mutex> lock(mutex); 
            if (events.size() < events.capacity())
            {
                was_empty = events.empty();
                events.push_back(event);
            }
            else
            {
                do
                {
                    condition.wait(lock);
                }
                while (events.size() == events.capacity());
                
                was_empty = events.empty();
                events.push_back(event);
            }
        }

        if (was_empty)
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
            
            if (events2.size() == events2.capacity())
            {
                condition.notify_one();
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
    std::vector<Event> events2;
    std::thread thread;
};

#endif


int main(int, char** argv)
{
    using Clock = std::chrono::high_resolution_clock;
    using namespace std::chrono;

    enum { num_iterations = 20 * 1000 };

    auto start_time = Clock::now();
    std::thread([]
    {
        Queue a;
        for (int i = 0; i != num_iterations; ++i)
        {
            a.post(i);
        }
    }).join();
    auto elapsed = duration_cast<milliseconds>(Clock::now() - start_time).count();
    std::cout << argv[0] << " " << elapsed << " ms.\n";
}


