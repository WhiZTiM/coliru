#include <iostream>
#include <chrono>
#include <type_traits>
#include <future>
#include <thread>

struct stop_watch
{
    using wall_clock = typename std::conditional< std::chrono::high_resolution_clock::is_steady,
                                                  std::chrono::high_resolution_clock,
                                                  std::chrono::steady_clock >::type ;

    const wall_clock::time_point start = wall_clock::now() ;
    wall_clock::time_point end = start ;

    stop_watch() = default ;

    void stop() { end = wall_clock::now() ; }

    unsigned long long elapsed() const
    { return std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() ; }

    template < typename CALLABLE, typename... ARGS >
    static unsigned long long time_it( CALLABLE&& fn, ARGS&&... args )
    {
        stop_watch sw ;
        std::forward<CALLABLE>(fn)( std::forward<ARGS>(args)... ) ;
        sw.stop() ;
        return sw.elapsed() ;
    }
};

void foo( unsigned int msecs )
{
    std::this_thread::sleep_for( std::chrono::milliseconds(msecs) ) ;
}

int main()
{
    auto future = std::async( std::launch::async, [] { return stop_watch::time_it( foo, 2345 ) ; } ) ;

    while( future.wait_for( std::chrono::milliseconds(300) ) != std::future_status::ready )
        std::cout << "waiting... " << std::flush ;

    std::cout << " for " << future.get() << " milliseconds\n" ;
}
