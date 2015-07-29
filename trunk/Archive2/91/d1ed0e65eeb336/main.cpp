#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
 
template <typename RAIter>
int parallel_sum(RAIter beg, RAIter end)
{
    std::cout << std::this_thread::get_id() <<std::endl;
    auto len = end - beg;
    if(len < 1000)
        return std::accumulate(beg, end, 0);
 
    RAIter mid = beg + len/2;
    auto handle = std::async(std::launch::async,
                              parallel_sum<RAIter>, mid, end);
    int sum = parallel_sum(beg, mid);
    return sum + handle.get();
}
 
int main()
{
    //std::vector<int> v(10000, 1);
    //std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 25; ++i)
    {
        auto fut = std::async(std::launch::async, []
        {          
            std::cout << std::this_thread::get_id() <<std::endl;
        });
        futures.push_back(std::move(fut));
    }
    std::for_each(futures.begin(), futures.end(), [](std::future<void> & fut)
    {
        fut.wait();
    });
}