#include <chrono>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

template<typename T>
long secs_since_epoch(T now) {
    return std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
}

int main()
{
    std::cout << "Seconds since epoch (steady clock): " << secs_since_epoch(std::chrono::steady_clock::now()) << '\n';
    std::cout << "Seconds since epoch (system clock): " << secs_since_epoch(std::chrono::system_clock::now()) << '\n';
    std::cout << "Seconds since epoch (hi-res clock): " << secs_since_epoch(std::chrono::high_resolution_clock::now()) << '\n';
    std::cout << "Seconds since epoch (Unix time() ): " << std::time(0) << '\n';
    return 0;
}
