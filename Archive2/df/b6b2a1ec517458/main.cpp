#include <iostream>
#include <ctime>
#include <chrono>
#include <utility>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <thread>

// return pair of elapsed processor_time, elapsed wall clock time (both in milliseconds)
template < typename FN, typename... ARGS >
std::pair<int, int> time_it( FN&& fn, ARGS&& ... args )
{
    using wall_clock = typename std::conditional< std::chrono::high_resolution_clock::is_steady,
                                                  std::chrono::high_resolution_clock,
                                                  std::chrono::steady_clock >::type ;
    const auto wc_start = wall_clock::now() ;
    const auto pc_start = std::clock() ;

    std::forward<FN>(fn)( std::forward<ARGS>(args)... ) ; // call the function

    const auto pc_end = std::clock() ;
    const auto wc_end = wall_clock::now() ;

    return { ( pc_end - pc_start ) * 1000.0 / CLOCKS_PER_SEC, // processor time millisecs
             std::chrono::duration_cast<std::chrono::milliseconds>( wc_end - wc_start ).count() } ;
}

void foo( std::vector<int>&& seq, unsigned int wait_period_in_ms )
{
    std::sort( seq.begin(), seq.end() ) ;
    std::this_thread::sleep_for( std::chrono::milliseconds(wait_period_in_ms) ) ;
}

int main()
{
    const auto times = time_it( foo, std::vector<int>( 32'000'000 ), 250 ) ;
    std::cout << " processor: " << times.first << " millisecs\n"
              << "wall clock: " << times.second << " millisecs\n" ;
    // perfect forwarding broken in g++ 5.1 ?              
}
