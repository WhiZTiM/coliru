#include <iostream>
#include <chrono>

int main()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::cout << seed << "\n";
    std::cout << std::chrono::system_clock::now().time_since_epoch().count() << "\n";
    
    return 0;
}
