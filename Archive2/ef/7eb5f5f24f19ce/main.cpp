#include <boost/lockfree/stack.hpp>
#include <iostream>
#include <chrono>


using Clock = std::chrono::high_resolution_clock;


enum { num_iterations = 10 * 1000 };


template<int pool_capacity>
void run()
{
    using Pool = boost::lockfree::stack<long, boost::lockfree::capacity<pool_capacity>>;

    Pool pool;
    auto size = 0;
    bool pushing = true;
    std::cout << "pool_capacity=" << pool_capacity << " sizeof(pool)=" << sizeof(pool) << ' ';

    auto start_time = Clock::now();
    for (auto i = 0; i != num_iterations; ++i)
    {
        if (pushing)
        {
            pool.push(i);
            if (++size == pool_capacity)
            {
                pushing = false;
            }
        }
        else
        {
            pool.pop(i);
            if (--size == 0)
            {
                pushing = true;
            }
        }
    }

    auto elapsed_time = Clock::now() - start_time;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_time).count();
    std::cout << (ns / num_iterations) << "ns/iteration" << std::endl;
}


int main()
{
	run<1>();
	run<2>();
	run<3>();
	run<4>();
	run<5>();
	run<6>();
	run<7>();
	run<8>();
	run<9>();
	run<10>();
	run<11>();
	run<12>();
	run<13>();
	run<14>();
	run<15>();
	run<16>();
	run<17>();
	run<18>();
	run<19>();
	run<20>();
}
