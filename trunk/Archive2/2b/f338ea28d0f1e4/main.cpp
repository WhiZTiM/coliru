#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <string>

std::mutex cout_lock ;

void repeat_print_message( unsigned int period_msecs, std::atomic<bool>& keep_running, std::string msg )
{
    const auto interval = std::chrono::milliseconds(period_msecs) ;
    int cnt = 0 ;

    while( keep_running )
    {
        {
            std::lock_guard<std::mutex> guard(cout_lock) ;
            std::cout << ++cnt << ". " << msg << '\n' << std::flush ;
        }

        std::this_thread::sleep_for(interval) ;
    }
}

int main()
{
    const std::string baba = "Baa, baa, black sheep," ;
    const std::string haveu = "Have you any wool?" ;
    std::atomic<bool> keep_running {true} ;

    std::thread( repeat_print_message, 200, std::ref(keep_running), baba ).detach() ; // every 200 ms
    std::thread( repeat_print_message, 500, std::ref(keep_running), haveu ).detach() ; // every 500 ms

    std::this_thread::sleep_for( std::chrono::seconds(3) ) ;
    keep_running = false ; // ask he threads to quit
    std::this_thread::sleep_for( std::chrono::milliseconds(500) ) ; // give them a bit of time to exit cleanly
}
