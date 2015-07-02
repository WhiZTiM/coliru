#include <algorithm>
#include <array>
#include <chrono>
#include <cstdlib>
#include <iostream>


template<int N>
bool branchless(const std::array<int, N>& lhs, const std::array<int, N>& rhs)
{
    bool result = true;
    for (auto i = 0; i != N; ++i)
    {
        result &= (lhs[i] == rhs[i]);
    }
    return result;
}

template<int N>
bool branchful(const std::array<int, N>& lhs, const std::array<int, N>& rhs)
{
    for (auto i = 0; i != N; ++i)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}


template<int N>
struct RandomNumberlist : std::array<int, N>
{
    RandomNumberlist()
    {
        for (auto& i : *this)
        {
            i = rand() % 4 != 0; // 
        }
    }
};
 
 

    
enum
{
    num_iterations = 10 * 1000
};


volatile long no_optimize;

template<int num_comparisons, typename F>
long run(const char* fname, F f)
{
    using namespace std::chrono;
    using Clock = high_resolution_clock;
    
    
    auto number_of_matches = 0ul;

    auto& a = *new std::array<RandomNumberlist<num_comparisons>, num_iterations>();
    auto& b = *new std::array<RandomNumberlist<num_comparisons>, num_iterations>();

    auto start_time = Clock::now();
    for (auto& el : a)
    {
        number_of_matches += f(el, b[&el - &a[0]]);
    }
    auto elapsed_time = duration_cast<microseconds>(Clock::now() - start_time).count();
    no_optimize += number_of_matches;

    (void)fname;
    return elapsed_time;
    delete &a;
    delete &b;
}


int main()
{
    #define RUN(n, f, g) \
    { std::cout << n << " " << std::flush; auto a = run<n>(#f " " #n, &f<n>); auto b = run<n>(#g " " #n, &g<n>); std::cout << int(0.5 + 10.0 * a / b) << ' ' << 10 << std::endl; }  \

    std::cout << "num_comparisons branchful branchless\n";
    RUN(1, branchful, branchless);
    RUN(2, branchful, branchless);
    RUN(3, branchful, branchless);
    RUN(4, branchful, branchless);
    RUN(5, branchful, branchless);
    RUN(6, branchful, branchless);
    RUN(7, branchful, branchless);
    RUN(8, branchful, branchless);
}
