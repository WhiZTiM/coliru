#include <limits>
#include <cstddef>
#include <cstdint>
#include <iostream>
int main()
{
    auto num =  std::numeric_limits<std::uint8_t>::max();
    std::cout << std::dec << num << "\n";
    std::cout << std::hex << num << "\n";
    
    
    std::cout << "int: " << std::dec << std::numeric_limits<int>::max()
              << " or " << std::hex << std::numeric_limits<int>::max() << '\n';
    
}