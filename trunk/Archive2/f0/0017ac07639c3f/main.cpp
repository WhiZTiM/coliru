#if FLAT_SET
#include <boost/container/flat_set.hpp>
#else
#include <set>
#endif
#include <chrono>
#include <iostream>


using value_type = long;


#if FLAT_SET
using Set = boost::container::flat_set<value_type>;
#else
using Set = std::set<value_type>;
#endif


Set generate_set(std::size_t size)
{
    Set result;
    for (auto i = 0 * size; i != size; ++i)
    {
        result.insert(i);
    }
    return result;
}


using Clock = std::chrono::steady_clock;


enum
{
    set_size = 1000 * 1000,
    num_lookups = 1000
};


volatile int no_optimization;


int main()
{
    using namespace std::chrono;
    
    
    auto before_time = Clock::now();
    auto set = generate_set(set_size);
    auto start_time = Clock::now();


    std::cout << "creation_time=" << duration_cast<milliseconds>(start_time - before_time).count() << "ms";

    int result = 0;
    for (auto i = 0; i != num_lookups; ++i)
    {
        result += *set.find(rand() % set.size());
    }

    no_optimization = result;

    auto elapsed_time = Clock::now();

    std::cout
        << " lookup_time=" << duration_cast<microseconds>(elapsed_time - start_time).count() << "us"
        << std::endl;
}

