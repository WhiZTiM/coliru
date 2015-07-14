#include <iostream>
#include <chrono>
#include <vector>
#include <tuple>

using namespace std;
using namespace std::chrono;

void function()
{
    long long number = 0;

    for( long long i = 0; i != 2000000; ++i )
    {
       number += 5;
    }
}

int main()
{
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    high_resolution_clock::time_point t3 = high_resolution_clock::now();
    high_resolution_clock::time_point t5 = high_resolution_clock::now();
    function();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    high_resolution_clock::time_point t6 = high_resolution_clock::now();

    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>( t4 - t3 ).count();
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>( t6 - t5 ).count();

    auto durations = std::make_tuple(duration1,duration2,duration3);

    std::vector<decltype(durations)> list;
    list.push_back(durations);

    cout << duration1 << " -- "<< duration2 << " -- "<< duration3 << " -- ";
    return 0;
}