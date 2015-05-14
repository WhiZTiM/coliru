#include <boost/lockfree/spsc_queue.hpp>
#include <atomic>
#include <condition_variable>
#include <cstring>
#include <iostream>
#include <math.h>
#include <mutex>
#include <system_error>
#include <thread>
#include <vector>
#include <semaphore.h>


unsigned long volatile g;
char padding[128];
std::atomic<int> counter{0};


struct Event
{
    Event(int n = 0) : n(n) {}

    void handle()
    {
        counter++;
        for (int i = 0; i != 10; ++i) g += g;
    }

    volatile int n;
};


#if SEMAPHORE



struct Semaphore
{
    Semaphore()
    {
        if (-1 == sem_init(&mSem, 0, 0))
        {
            throw std::system_error(std::error_code(errno, std::system_category()), strerror(errno));
        }
    }

    ~Semaphore()
    {
        if (-1 == sem_destroy(&mSem))
        {
            // silently discard error
        }
    }

    Semaphore(const Semaphore&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;

    void post()
    {
        if (-1 == sem_post(&mSem))
        {
            throw std::system_error(std::error_code(errno, std::system_category()), strerror(errno));
        }
    }

    void wait()
    {
        if (-1 == sem_wait(&mSem))
        {
            throw std::system_error(std::error_code(errno, std::system_category()), strerror(errno));
        }
    }

private:
    mutable sem_t mSem;
};

struct Queue
{
    Queue() : mSem(), mQueue(), mThread([this]{ consumer_thread(); })
    {
        sched_yield();
    }

    ~Queue()
    {
        while (!mQueue.push(-1)) { sched_yield(); }
        mSem.post();
        mThread.join();
    }

    void post(Event event)
    {
        while (!mQueue.push(event)) { sched_yield(); }
        mSem.post();
    }

    void consumer_thread()
    {
        for (;;)
        {
            mSem.wait();
            Event event;
            mQueue.pop(event);
            if (event.n == -1)
            {
                return;
            }
            event.handle();
        }
    }

    Semaphore mSem;
    char padding1[128 - sizeof(mSem)];
    boost::lockfree::spsc_queue<Event, boost::lockfree::capacity<800>> mQueue;
    char padding2[128];
    std::thread mThread;
};


#else


struct Queue
{
    Queue() : thread([this]{ consumer_thread(); })
    {
        sched_yield();
        events.reserve(800);
        events2.reserve(800);
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
        bool notify = false;

        {
            std::unique_lock<std::mutex> lock(mutex); 
            if (events.size() < events.capacity())
            {
            doit:
                notify = events.empty();
                events.push_back(event);
            }
            else
            {
                do
                {
                    condition.wait(lock);
                }
                while (events.size() == events.capacity());
                goto doit;
            }
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

    enum { num_iterations = 1000 * 1000 };

    auto start_time = Clock::now();
    std::thread([]
    {
        Queue a;
        sched_yield();
        for (int i = 0; i != num_iterations; ++i)
        {
            a.post(i);
        }
    }).join();
    auto elapsed = duration_cast<milliseconds>(Clock::now() - start_time).count();
    std::cout << argv[0] << ": " << counter <<  " time_=" << elapsed << " ms.\n";
}

