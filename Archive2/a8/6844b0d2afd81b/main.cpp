#include <iostream>
#include <future>
#include <thread>
 #include <chrono>
 #include <exception>
int main()
{
    {
    std::future<int> f2 = std::async([]()
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "ala" << std::endl;
        throw std::runtime_error("al");
        return 1;
        });
    }
    std::cout << "dupa" << std::endl;
}