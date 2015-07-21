#include <iostream>
#include <unordered_set>
#include <set>
#include <chrono>
#include <random>
#include <limits>
#include <iterator>
#include <algorithm>

template<typename TimeT = std::chrono::milliseconds>
struct measure
{
    template<typename F, typename ...Args>
    static typename TimeT::rep execution(F func, Args&&... args)
    {
        auto start = std::chrono::system_clock::now();
        func(std::forward<Args>(args)...);
        auto duration = std::chrono::duration_cast< TimeT> 
                            (std::chrono::system_clock::now() - start);
        return duration.count();
    }
};

int f(int low, int high)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(low, high);

    return dis(gen);
}

int main()
{
    int num, m(std::numeric_limits<int>::min()), M(std::numeric_limits<int>::max()); 
    
    std::set<int> os;
    std::unordered_set<int> us;
    
    for (int i = 0; i < 100000; ++i)
    {
        num = f(m, M); 
        os.insert(num), us.insert(num);
    }
        
    long long t = 0;
    
    for (int rep = 0; rep < 3; ++rep)
    {    
        std::cout << "os " << measure<std::chrono::microseconds>::execution([&]{
            auto i = os.begin(); 
            std::advance(i, 100000-1); 
            t += *i;
        }) << " microseconds\n";
     
        std::cout << "us " << measure<std::chrono::microseconds>::execution([&]{
            auto i = os.begin(); 
            std::advance(i, 100000-1); 
            t += *i;   
        }) << " microseconds\n";
    }

    return t;
}
