#include <chrono>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>

int main() {
    using Clock = std::chrono::system_clock; 
    const auto now = Clock::now();
    const auto nowTimeT = Clock::to_time_t(now);
    const auto nowTm = std::localtime(&nowTimeT);
    
    std::ostringstream monthStream;
    if (monthStream << std::put_time(nowTm, "%B")) {
        std::cout << "The month is " << monthStream.str() << '\n';
    } else {
        std::cout << "Failed to get month.\n";
    }
}