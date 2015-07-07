#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <chrono>
#include <thread>



int main ()
{
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

    auto epoch = now.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::microseconds>(epoch);
    long duration = value.count();

    std::cout << "Duration=" << duration << std::endl;  
        
    std::chrono::milliseconds ms(duration);

    std::chrono::time_point<std::chrono::system_clock> dt(ms);

    auto epoch1 = dt.time_since_epoch();
    auto value1 = std::chrono::duration_cast<std::chrono::microseconds>(epoch1);
    long duration1 = value1.count();
    std::cout << "Duration1=" << duration1 << std::endl;  

    if (dt != now)
        std::cout << "Failure." << std::endl;
    else
        std::cout << "Success." << std::endl;
}

