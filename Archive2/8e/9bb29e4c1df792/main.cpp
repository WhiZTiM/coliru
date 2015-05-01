#include <atomic>
#include <cassert>
#include <iostream>
#include <mutex>
#include <thread>


#ifdef NORMAL_MUTEX
#define MUTEX_TYPE PTHREAD_MUTEX_INITIALIZER
#elif ADAPTIVE_MUTEX
#define MUTEX_TYPE PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP
#endif


struct Mutex
{
    Mutex() { mtx = MUTEX_TYPE; }

    ~Mutex() { pthread_mutex_destroy(&mtx); }

    Mutex(const Mutex&) = delete;
    Mutex& operator=(const Mutex&) = delete;

    void lock() { pthread_mutex_lock(&mtx); }

    void unlock() { pthread_mutex_unlock(&mtx); }

private:
    pthread_mutex_t mtx;
};


long counter;
Mutex mtx;
std::atomic<bool> quit;


std::thread t1([]
{
    while (!quit)
    {
        std::lock_guard<Mutex> lock(mtx);
        counter++;
    }
});

std::thread t2([]
{
    while (!quit)
    {
        std::lock_guard<Mutex> lock(mtx);
        counter++;
    }
});

int main()
{
    for (;;)
    {
        std::lock_guard<Mutex> lock(mtx);
        if (counter > 0) break;
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    quit = true;
    t1.join();
    t2.join();
    
    std::cout << "counter=" << counter << std::endl;
}
