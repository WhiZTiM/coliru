#include <boost/function.hpp>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>



void* operator new(std::size_t n)
{
    std::printf("new %d\n", static_cast<int>(n));
    return std::malloc(n);
}


int main()
{
    std::uint64_t a = 1, b = 2, c = 3, d = 4;
    
    std::cout << "std::function:" << std::endl;
    std::function<void()>([a] {});              // allocates 8 bytes
    std::function<void()>([a, b] {});           // allocates 16 bytes
    std::function<void()>([a, b, c] {});        // allocates 24 bytes
    std::function<void()>([a, b, c, d] {});     // allocates 32 bytes
    
    
    std::cout << "\nboost::function:" << std::endl;     
    boost::function<void()>([a] {});            // no allocation
    boost::function<void()>([a, b] {});         // no allocation
    boost::function<void()>([a, b, c] {});      // no allocation
    boost::function<void()>([a, b, c, d] {});   // allocates 32 bytes
}
