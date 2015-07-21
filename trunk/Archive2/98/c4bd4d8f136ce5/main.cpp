#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    std::cout << "yo" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << "whats" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "up" << std::endl;

    std::cin.get();
    return 0;
}