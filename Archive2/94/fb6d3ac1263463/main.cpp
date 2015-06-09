#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>


template<bool Enabled>
struct Benchmark
{
    using Clock = std::chrono::high_resolution_clock;
    
    Benchmark() :
        start_time_(Enabled ? Clock::now() : Clock::time_point())
    {
    }
    
    ~Benchmark()
    {
        if (Enabled)
        {
            std::cout << "Benchmark: " << std::chrono::duration_cast<std::chrono::microseconds>(elapsed()).count() << "us elapsed" << '\n';
        }
    }
    
    Clock::duration elapsed()
    {
        if (Enabled) return Clock::now() - start_time_;
        else return Clock::duration();
    }
    
    
    Clock::time_point start_time_;
};


std::atomic<bool> quit;



void work()
{
    // meh
}


template<bool Enabled>
void run(Benchmark<Enabled> benchmark)
{
    unsigned long iterations = 0;
    while (!quit)
    {
        ++iterations;
        
        std::cout << iterations << ' ';
        
        if (!Enabled)
        {
            // Run normally for 1000 iterations.
            if (iterations % 1000 == 0)
            {                
                std::cout << "\nSTART BENCHMARK" << '\n';
                run(Benchmark<true>());
            }
        }
        else
        {
            // Run benchmark for 10 iterations
            if (iterations % 10 == 0)
            {
                std::cout << "\nSTOP BENCHMARK" << '\n';
                return;
            }
        }
        
        work();
    }
}



int main()
{
    std::thread t([]{ run(Benchmark<false>{}); });
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    quit = true;
    t.join();
}

