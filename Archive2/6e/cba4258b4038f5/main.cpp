#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
 
template <typename RAIter>
int parallel_sum(RAIter beg, RAIter end)
{
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
    auto f = std::async(std::launch::async, [](){
                            std::cout<<"This is from async Lambad"<<std::endl;
                            return 0;
                            });
        f.get();
}