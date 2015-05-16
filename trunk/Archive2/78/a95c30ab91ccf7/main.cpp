#include <limits>
#include <cstddef>
#include <cstdint>
#include <iostream>
int main()
{
    std::uint8_t num =  std::numeric_limits<std::uint8_t>::max();
    std::cout << "Decimal" << static_cast<std::int8_t>(num) << "\n";
    std::cout << "Hex" << std::hex << static_cast<std::int8_t>(num) << "\n";
    
    
    std::cout << "int: " << std::dec << std::numeric_limits<int>::max()
              << " or " << std::hex << std::numeric_limits<int>::max() << '\n';
    
}