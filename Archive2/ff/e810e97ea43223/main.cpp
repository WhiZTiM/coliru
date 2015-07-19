#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <string>

void sleep_for( unsigned int millisecs )
{ std::this_thread::sleep_for( std::chrono::milliseconds(millisecs) ) ; }

const std::string now()
{
    std::time_t t = std::time(nullptr);
    return std::asctime( std::localtime( std::addressof(t) ) );
}

int main()
{
    std::cout << now() << std::flush ;
    sleep_for(2200) ; // 2.2 seconds
    std::cout << now() << std::flush ;
    sleep_for(1800) ; // 1.8 seconds
    std::cout << now() << std::flush ;
    sleep_for(3000) ; // three seconds
    std::cout << now() << std::flush ;
}
