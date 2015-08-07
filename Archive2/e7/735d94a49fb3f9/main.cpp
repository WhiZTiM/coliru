#include <iostream>
#include <mutex>
#include <thread>
#include <future>
#include <vector>
#include <utility>
#include <chrono>


struct Worker {

    std::mutex mutex;
    
    std::vector<std::packaged_task<void()>> tasks;
    std::mutex vector_mutex;

    std::atomic_flag quit_flag;
    std::condition_variable inner_cv;
    std::condition_variable outer_cv;

    std::thread t,u;

    void thread_func(std::promise<void> start_) {                
        decltype(tasks) local_tasks_;
        std::unique_lock<std::mutex> lock_{mutex};
        start_.set_value();                
        while (quit_flag.test_and_set(std::memory_order_acquire)) {   
           inner_cv.wait(lock_);
           {
             std::unique_lock<std::mutex> lock_{vector_mutex};             
             local_tasks_.swap(tasks);           
           }
           for (auto&& e : local_tasks_) {
               e();
           }                           
           local_tasks_.clear();
        }
        quit_flag.clear();
    }

    void babysitter(std::promise<void> start_) {        
        std::unique_lock<std::mutex> lock_{mutex};
        start_.set_value();                
        while (quit_flag.test_and_set(std::memory_order_acquire)) {
            outer_cv.wait(lock_);
            inner_cv.notify_one();
        }
        quit_flag.clear();
    }


    Worker() {
        quit_flag.test_and_set();
        std::promise<void> p1,p2;
        std::future<void> f1 = p1.get_future(),
                          f2 = p2.get_future();                                
        u = std::thread{&Worker::babysitter,this,std::move(p1)};  f1.get();
        std::unique_lock<std::mutex>{mutex}; // waiting on the cv.. and done        
        t = std::thread{&Worker::thread_func,this,std::move(p2)};  f2.get();
        std::unique_lock<std::mutex>{mutex}; // waiting on the other cv.. and done
    }

    template <typename F>
    void deposit_task(F&& func) {
        std::unique_lock<std::mutex> lock_{vector_mutex};
        tasks.emplace_back(std::packaged_task<void()>{std::move(func)});
        outer_cv.notify_one();
    }

    void deposit_task(std::packaged_task<void()> task_) {            
        std::unique_lock<std::mutex> lock_{vector_mutex};
        tasks.emplace_back(std::move(task_));
        outer_cv.notify_one();
    }

    ~Worker() {
            { // local block
            std::unique_lock<std::mutex> lock_{mutex};
            quit_flag.clear();
            outer_cv.notify_one();  
            }

        u.join();
        t.join();        
    }

};

int main() {

    auto then = std::chrono::high_resolution_clock::now();        
    volatile int vi = 0;
    
    {        
        Worker et;
        
        for (int i = 0; i < 1000000; ++i) { 
            et.deposit_task([&](){            
                                ++vi;
                            }); 
        }                 
        std::cout << "Waiting for it to finish..\n";            
    }

    auto now = std::chrono::high_resolution_clock::now();
    std::cout << "\nDuration == " << std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count() << " millseconds\n";
    std::cout << "vi == " << vi << "\n";
}   