#include <iostream>
#include <string>

#include <boost/asio/ip/address.hpp>
#include <boost/system/error_code.hpp>


int main()
{
    std::string ip = "33.66.77.99";
    
    //This works...
    boost::asio::ip::address test = boost::asio::ip::address::from_string(ip);
    
    //This results in 0.0.0.0
    //boost::asio::ip::address test;
    //test.from_string(ip);
    
    
    std::cout << test.to_string() << std::endl;
}
