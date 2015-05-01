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
    std::function<void()>([a] {});              // allocates 0 bytes
    std::function<void()>([a, b] {});           // allocates 0 bytes
    std::function<void()>([a, b, c] {});        // allocates 0 bytes
    std::function<void()>([a, b, c, d] {});     // allocates 40 bytes
}
