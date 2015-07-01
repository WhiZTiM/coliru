#include <atomic>
#include <map>
#include <condition_variable>
#include <cstring>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>



__attribute((aligned(128))) std::atomic<bool> quit;
enum { max_queue_size = 10000 };


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





template<typename T>
struct Queue
{
    Queue()
    {
        mItems.reserve(max_queue_size);
        mItems2.reserve(max_queue_size);
    }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    ~Queue()
    {
        stop();
    }

    void stop()
    {
        std::unique_lock<std::mutex> lock(mMutex);
        mStopped = true;
        mCondition.notify_all();
    }

    void push(const T& item)
    {
        bool was_empty = false;

        // this scope for the lock
        {
            #ifdef SPINLOCK
            while (!mMutex.try_lock())
            {
                asm volatile ("pause;");
            }
            std::unique_lock<std::mutex> lock(mMutex, std::adopt_lock);
            #else
            std::unique_lock<std::mutex> lock(mMutex);
            #endif
            if (mItems.size() < mItems.capacity())
            {
                was_empty = mItems.empty();
                mItems.push_back(item);
            }
            else
            {
                do
                {
                    mCondition.wait(lock);
                    if (mStopped) return;
                }
                while (mItems.size() == mItems.capacity());

                was_empty = mItems.empty();
                mItems.push_back(item);
            }
        }

        if (was_empty)
        {
            mCondition.notify_one();
        }
    }

    // ConsumeFunction must be a callable object with signature:
    //   void(Item* first, std::size_t length)
    template<typename ConsumeFunction>
    void consume_all(ConsumeFunction&& consume_function)
    {
        auto was_full = false;

        // this scope for the lock
        {
            #ifdef SPINLOCK
            while (!mMutex.try_lock())
            {
                asm volatile ("pause;");
            }
            std::unique_lock<std::mutex> lock(mMutex, std::adopt_lock);
            #else
            std::unique_lock<std::mutex> lock(mMutex);
            #endif
            if (mStopped) return;
            while (mItems.empty())
            {
                mCondition.wait(lock);
                if (mStopped) return;
            }
            was_full = mItems.size() == mItems.capacity();
            std::swap(mItems, mItems2);
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

        consume_function(mItems2.data(), mItems2.size());
        mItems2.clear();
    }


    __attribute((aligned(128))) bool mStopped{false};
    __attribute((aligned(128))) std::vector<T> mItems;
    __attribute((aligned(128))) std::vector<T> mItems2;
    __attribute((aligned(128))) std::condition_variable mCondition;
    __attribute((aligned(128))) std::mutex mMutex;
};


enum { num_iterations = 10 * 1000 * 1000 };

int64_t num_consumed = 0;
int64_t sum_latency = 0;
int64_t min_latency = std::numeric_limits<int64_t>::max();
int64_t max_latency = 0;
int64_t sum_batch = 0;

std::chrono::milliseconds timeout(200);


void run()
{
    using Clock = std::chrono::high_resolution_clock;
    Queue<Clock::time_point> queue;


    std::thread producer_thread([&queue]
    {
        while (!quit)
        {
            queue.push(Clock::now());
        }
        queue.stop();
    });

    std::thread consumer_thread([&queue]
    {
        while (!quit)
        {
            queue.consume_all([](Clock::time_point* time_points, std::size_t length) 
            {
                num_consumed += length;
                for (auto i = 0u; i != length; ++i)
                {
    				auto consume_time = Clock::now();
                    auto latency_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(consume_time - time_points[i]).count();
                    sum_latency += latency_ns;
                    if (latency_ns < min_latency) min_latency = latency_ns;
                    if (latency_ns > max_latency) max_latency = latency_ns;
                }
            });
        }
        std::cout
        #ifdef SPINLOCK
            << " SPINNING "
        #else
            << "  LOCKING "
        #endif
            << " min_latency_ns=" << min_latency
            << " max_latency_ns=" << max_latency
            << " avg_latency_ns=" << uint64_t(0.5 + 1.0 * sum_latency / num_consumed)
            << " throughput=" << uint64_t(0.5 + 1.0 * num_consumed / timeout.count()) << "events/ms"
            << '\n';
    });

    // run the threads until timeout
    std::this_thread::sleep_for(timeout);

    // Posting the stop signals
    quit = true;
    queue.stop();

    // Joining threads
    producer_thread.join();
    consumer_thread.join();

}


int main()
{
    run();
}
