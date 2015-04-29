#include <iostream>
#include <chrono>
#include <thread>
 
void barry()
{
    std::this_thread::sleep_for(std::chrono::microseconds(1000000));
}
 
int main()
{
    auto t1 = std::chrono::high_resolution_clock::now();
    barry();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "barry() took "
              << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count()
              << " barrys\n";
}