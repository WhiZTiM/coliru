#include <iostream>
#include <unordered_set>
#include <set>
#include <chrono>

struct Timer
{
    Timer() { reset(); }
    void reset() { start_ = std::chrono::high_resolution_clock::now(); }
    void stop() { stop_ = std::chrono::high_resolution_clock::now(); }
    double elapsed() { return (stop_ - start_).count(); }
    std::chrono::time_point<std::chrono::high_resolution_clock> start_, stop_;
};

int main()
{
    std::set<int> os;
    std::unordered_set<int> us;
    for (int i = 0; i < 1000000; ++i)
        os.insert(i), us.insert(i);
        
    long long t = 0;
    
    for (int rep = 0; rep < 3; ++rep)
    {
        Timer timer;
        for (auto i = os.begin(); i != os.end(); ++i)
            t += *i;
        timer.stop();
        std::cout << "os " << timer.elapsed() << '\n';
        timer.reset();
        for (auto i = us.begin(); i != us.end(); ++i)
            t += *i;
        timer.stop();
        std::cout << "us " << timer.elapsed() << '\n';
    }

    return t;
}
