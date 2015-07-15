#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>
#include <vector>

struct A // per-thread singleton
{
    static A& instance() ;

    private:
        A() { /* ... */ };
        A( const A& ) = delete ; // non-copyable
        A( A&& ) = delete ; // non-moveable
};

A& A::instance() // Meyer's singleton 
{
    thread_local static A singleton ; // one singleton per thread
    return singleton ;
}

const void* test_it()
{
    A& a1 = A::instance() ;
    A& a2 = A::instance() ;

    {
        static std::atomic<int> cnt{0} ;
        
        static std::mutex stdout_lock ;
        std::lock_guard<std::mutex> lock(stdout_lock) ;
        std::cout << "thread #" << ++cnt << ": A::instance at " << std::addressof(a1) 
                  << ' ' << std::addressof(a2) << '\n' << std::flush ;
    }

    std::this_thread::sleep_for( std::chrono::milliseconds(100) ) ;

    return std::addressof( A::instance() ) ;
}

int main()
{
    std::vector< std::future< const void* > > futures ;
    constexpr int NTHREADS = 5 ;

    for( int i = 0 ; i < NTHREADS ; ++i )
        futures.push_back( std::async( std::launch::async, test_it ) ) ;

    std::this_thread::sleep_for( std::chrono::milliseconds(500) ) ;
    
    std::cout << "--------------\n" ;
    for( auto& future : futures ) std::cout << " object *was* at address: " << future.get() << '\n' ;
}
