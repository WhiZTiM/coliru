#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <set>
#include <mutex>
#include <vector>
#include <fstream>
#include <future>

namespace
{
    std::set<std::thread::id> ids ;
    std::mutex big_lock ;
}

std::string reverse( const std::string& str )
{
    {
        std::lock_guard<std::mutex> lock(big_lock) ;
        ids.insert( std::this_thread::get_id() ) ;
    }

    return { str.rbegin(), str.rend() } ;
}

int main()
{
    ids.insert( std::this_thread::get_id() ) ;
    
    
    std::ifstream file( __FILE__ ) ;
    std::vector< std::future<std::string> > futures ;

    std::string str ;
    // good implementations would (re)use a thread from the thread pool
    while( file >> str ) futures.push_back( std::async( std::launch::async, reverse, str ) );
    
    std::thread( reverse, "abracadabra" ).detach() ; // this must be a new thread

    for( auto& future : futures ) future.get() ;
    std::cout << "hardware concurrency: " << std::thread::hardware_concurrency() << '\n'
              << "#unique thread ids: " << ids.size() << '\n' ;
}
