#include <iostream>
#include <future>
#include <mutex>
#include <thread>
#include <chrono>

std::mutex cout_lock ; // http://en.cppreference.com/w/cpp/thread/mutex

void counter( int from, int to, int interval_in_ms, char id )
{
    // http://en.cppreference.com/w/cpp/chrono/duration
    const auto interval = std::chrono::milliseconds(interval_in_ms) ;

    for( int i = from ; i < to ; ++i )
    {
        // http://en.cppreference.com/w/cpp/thread/sleep_for
        std::this_thread::sleep_for(interval) ;

        // http://en.cppreference.com/w/cpp/thread/lock_guard
        std::lock_guard<std::mutex> guard(cout_lock) ;

        std::cout << '+' << id << std::flush ;
    }

    for( int i = to ; i > from ; --i )
    {
        std::this_thread::sleep_for(interval) ;
        std::lock_guard<std::mutex> guard(cout_lock) ;
        std::cout << '-' << id << std::flush ;
    }
}

int main()
{
    // http://en.cppreference.com/w/cpp/thread/async
    // http://en.cppreference.com/w/cpp/thread/future
    auto fa = std::async( std::launch::async, counter, 0, 40, 100, 'a' ) ;
    auto fb = std::async( std::launch::async, counter, 0, 80, 50, 'b' ) ;

    for( int i = 0 ; i < 10 ; ++i )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds(800) ) ;
        std::lock_guard<std::mutex> guard(cout_lock) ;
        std::cout << "(main)\n" << std::flush ;
    }
    // wait for destructors of fb, fa
}
