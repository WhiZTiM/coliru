#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

using namespace std;

void dot_product(const std::vector<int>& v1, const std::vector<int>& v2, int& result, int rangeLeft, int rangeRight)
{
//    cout << "Thread started. [" << rangeLeft << " - " << rangeRight << "]" <<endl;
    for(auto i = rangeLeft; i < rangeRight; ++i )
    {
        result += v1[i] * v2[i];
    }
}
   
std::vector<int>
bounds(unsigned int ranges, int lower_limit, int upper_limit)
{
    std::vector<int> result;
    result.reserve(ranges+1);
    auto steps = (upper_limit - lower_limit) / ranges;
    for (unsigned int i = 0; i<=ranges; ++i)
    {
        result.push_back(lower_limit + i * steps);
    }
    return result;
}

typedef std::chrono::milliseconds milliseconds;

int main()
{
    unsigned int nr_elements = {100 * 1000 *1000};
    unsigned int nr_threads  = {2};
    int result{0};
    
    auto threads = std::vector<std::thread>();

    auto vector1 = std::vector<int>(nr_elements, 1);   // vector has nr_elements, all of them are 1.
    auto vector2 = std::vector<int>(nr_elements, 2);   // vector has nr_elements, all of them are 2.

    auto limits = bounds(nr_threads, 0, nr_elements);
    cout << "Threads: " << nr_threads << " Elements: " << nr_elements << endl;
    auto t0 = std::chrono::high_resolution_clock::now();
    for(unsigned int i =0; i<nr_threads; ++i)
    {
        threads.push_back(std::thread(dot_product
                                      , std::ref(vector1)
                                      , std::ref(vector2)
                                      , std::ref(result)
                                      , limits[i]
                                      , limits[i+1]));
    }
//    std::cout << "Launched from main." << std::endl;

    for (auto& thread : threads)
    {
        thread.join();
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    auto total_ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
    std::cout << "Elapsed time: " << total_ms.count() << "ms" <<std::endl;

    std::cout << result << std::endl;
    return 0;
}

