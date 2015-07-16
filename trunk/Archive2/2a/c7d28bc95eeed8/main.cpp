#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>


template<typename Data>
class concurrent_queue
{
private:
    mutable std::mutex the_mutex;
    std::condition_variable the_condition_variable;
    std::vector<Data> the_queue;
    
    // adding a second queue
    // it will only be accessed by the consumer so it does not require locking
    // also it's aligned to 128 bytes to prevent false sharing
    __attribute((aligned(128))) std::vector<Data> the_queue2;
    
    
public:
    void push(Data const& data)
    {
        bool was_empty = false;
        
        {
            std::lock_guard<std::mutex> lock(the_mutex);
            was_empty = the_queue.empty();
            the_queue.push_back(data);
        }
        
        if (was_empty)
        {
            the_condition_variable.notify_one();
        }
    }
    
    template<typename F>
    std::size_t consume_all(F&& f)
    {   
        // minimize the scope of the lock
        {
            std::lock_guard<std::mutex> lock(the_mutex);
            std::swap(the_queue, the_queue2);
        }
        
        // process all items from the_queue2 in batch
        for (auto& item : the_queue2)
        {
            f(item);
        }
        
        auto result = the_queue2.size();        
        the_queue2.clear(); // clearing the queue (while preserving the memory!)
        return result;
    }
};


using Clock = std::chrono::high_resolution_clock;
concurrent_queue<Clock::time_point> q;
std::atomic<int> state{0};

    
int main()
{   
    enum { num_iterations = 1000 };
    
    std::thread t1([]
    {
        state++;
        for (auto i = 0; i != num_iterations; ++i)
        {
            q.push(Clock::now());
        }
    });
    
    
    auto num_consumed = 0;
    auto start_time = Clock::now();
    
    while (state != 1); // wait until thread t1 has started
    
    while (num_consumed != num_iterations)
    {
        auto batch_size = q.consume_all([&num_consumed, start_time](Clock::time_point item) mutable
        {
            std::cout << (item - start_time).count() << '\n';
            num_consumed++;
        });
        
        if (batch_size > 0)
        {
            std::cout << "Processed " << batch_size << " items in batch.\n";
        }
    }    
    
    std::cout << "Joining thread t1." << std::endl;    
    t1.join();
}

