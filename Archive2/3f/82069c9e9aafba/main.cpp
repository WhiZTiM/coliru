#include <boost/asio.hpp>
#include <boost/optional.hpp>
#include <chrono>
#include <future>
#include <iostream>


using namespace std::chrono;
using namespace boost::asio;


io_service ios;


template<typename F>
auto post_after(F&& f, microseconds delay) -> std::future<decltype(f())>
{
    using R = decltype(f());
    
    auto result = std::make_shared<boost::optional<R>>();   
    
    // First schedule the asynchronous task.
    auto timer = std::make_shared<deadline_timer>(ios);        
    timer->expires_from_now(boost::posix_time::microseconds(delay.count()));    
    timer->async_wait([f, result](const boost::system::error_code& error) {
        if (error) throw boost::system::system_error(error);
        *result = f();
    });
    
    // Next use std::async with the *deferred* launch policy to
    // create a task which performs the blocking wait and returns
    // the result.
    return std::async(std::launch::deferred, [result, timer] {
        while (!*result) {
            if (ios.stopped()) ios.reset();
            ios.run_one();
        }
        return **result;
    });
}


int main()
{
    auto start_time = high_resolution_clock::now();
    
    std::future<int> future1 = post_after([]{ return 1; }, milliseconds(10));
    std::future<int> future2 = post_after([]{ return 2; }, milliseconds(20));    
    std::future<int> future3 = post_after([]{ return 3; }, milliseconds(30));
    
    std::cout << future1.get() << '\n';
    std::cout << future2.get() << '\n';
    std::cout << future3.get() << '\n';
    
    std::cout << "elapsed time: " << duration_cast<milliseconds>(high_resolution_clock::now() - start_time).count() << "ms\n";
}
