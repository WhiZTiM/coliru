#include <iostream>

#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/system/error_code.hpp>
#include <chrono>

int main()
{
    boost::asio::io_service io_service;
    boost::asio::steady_timer poll_timer(io_service);
    
    poll_timer.expires_from_now(std::chrono::milliseconds(50));
    poll_timer.async_wait([&](boost::system::error_code const& ec)
    {
        std::cout << "Trigger 1" << std::endl;
        
        std::size_t number_of_operations_cancelled =
                poll_timer.expires_from_now(std::chrono::milliseconds(50));
                
        std::cout << "Operations cancelled: " << number_of_operations_cancelled << std::endl;
        
        poll_timer.async_wait([&](boost::system::error_code const& ec)
        {
            std::cout << "Trigger 2" << std::endl;
        });
    });
    
    io_service.run();
}
