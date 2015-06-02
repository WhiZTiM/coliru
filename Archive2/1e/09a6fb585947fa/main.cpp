#include <iostream>
#include <chrono>

int main()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::cout << seed << "\n";
    
    return 0;
}
