#include "tbb/concurrent_queue.h"
#include <atomic>
#include <condition_variable>
#include <cstring>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>




std::atomic<std::uint64_t> events_handled{0}; char padding1[128 - sizeof(events_handled)];
std::atomic<bool> gGlobalQuitFlag{false};     char padding2[128 - sizeof(gGlobalQuitFlag)];
std::atomic<std::uint64_t> events_posted{0};  char padding3[128 - sizeof(events_posted)];
static long volatile g;                       char padding4[128 - sizeof(g)];



enum { max_queue_size = 500 };


struct LogItem
{
    ~LogItem()
    {
        static std::mutex m;
        std::lock_guard<std::mutex> l(m);
        std::cout << ss.str() << std::endl;
    }
    std::stringstream ss;
};


#define LOG() if (0) ; else LogItem().ss


enum : uint64_t { StopSignal = std::numeric_limits<std::uint64_t>::max() };


struct Event
{
    Event(std::uint64_t n = 0) : n(n) {}

    void handle()
    {
        if (n == StopSignal) return;

        // do some work
        for (int i = 0; i != 50; ++i)
        {
            g += g;
        }

        events_handled++;
    }

    volatile std::uint64_t n;
};



struct Queue
{
    Queue()
    {
        mEvents.reserve(max_queue_size);
        mEvents2.reserve(max_queue_size);
    }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void post(Event event)
    {
        if (event.n == StopSignal)
        {
            mStopped = true;
            mCondition.notify_all();
            return;
        }

        bool was_empty = false;

        // this scope for the lock
        {
            std::unique_lock<std::mutex> lock(mMutex);
            if (mEvents.size() < mEvents.capacity())
            {
                was_empty = mEvents.empty();
                mEvents.push_back(event);
            }
            else
            {
                do
                {
                    mCondition.wait(lock);
                    if (mStopped) return;
                }
                while (mEvents.size() == mEvents.capacity());

                was_empty = mEvents.empty();
                mEvents.push_back(event);
            }
        }

        if (was_empty)
        {
            mCondition.notify_one();
        }
    }

    // F must be callbable with signature:
    //   void(Event* first, std::size_t length)
    template<typename F>
    void consume_all(F&& f)
    {
        auto was_full = false;

        // this scope for the lock
        {
            std::unique_lock<std::mutex> lock(mMutex);
            while (mEvents.empty())
            {
                mCondition.wait(lock);
                if (mStopped) return;
            }
            was_full = mEvents.size() == mEvents.capacity();
            std::swap(mEvents, mEvents2);
        }

        // We only need to notify the producers if the queue was full.
        if (was_full)
        {
            // condition.notify_all will cause all producers to wake up.
            // Of course, only one producer can lock the mutex at a time,
            // but they will all return from the wait as soon as they
            // get the mutex.
            mCondition.notify_all();
        }

        f(mEvents2.data(), mEvents2.size());
        mEvents2.clear();
    }


    std::atomic<bool> mStopped{false};   char padding1[128 - sizeof(mStopped)];
    std::vector<Event> mEvents;          char padding2[128 - sizeof(mEvents)];
    std::vector<Event> mEvents2;         char padding3[128 - sizeof(mEvents2)];
    std::condition_variable mCondition;  char padding4[128 - sizeof(mCondition)];
    std::mutex mMutex;                   char padding5[128 - sizeof(mMutex)];
};


enum { num_iterations = 10 * 1000 * 1000 };


void run()
{
    Queue queue;

    using Clock = std::chrono::high_resolution_clock;
    auto start_time = Clock::now();

    std::thread producer_thread([&queue]
    {
        while (!gGlobalQuitFlag)
        {
            queue.post(++events_posted);
        }
        queue.post(StopSignal);
    });

    std::thread consumer_thread([&queue]
    {
        while (!gGlobalQuitFlag)
        {
            queue.consume_all([](Event* events, std::size_t length)
            {
                for (auto i = 0u; i != length; ++i)
                {
                    auto& event = events[i];
                    if (event.n == StopSignal) return;
                    event.handle();
                }
            });
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Posting the stop signals
    gGlobalQuitFlag = true;
    queue.post(StopSignal);

    // Joining threads
    producer_thread.join();
    consumer_thread.join();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - start_time);

    LOG() << "Program finished:"
          << " duration: " << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_ns).count() << "ms"
          << " events_handled=" << events_handled << " (" <<  int(elapsed_ns.count() / events_posted) << " ns/event)"
          ;
}


int main()
{
    LOG() << "=== New Run === ";
    run();
    run();
    run();
}
