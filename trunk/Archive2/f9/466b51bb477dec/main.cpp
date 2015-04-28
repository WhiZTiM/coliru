#include <iostream>
#include <cstdint>
#include <cstring>
 
int main()
{
    // simple usage
    char source[] = "once upon a midnight dreary...", dest[4];
    std::memcpy(dest, source, sizeof dest);
    for (char c : dest)
        std::cout << c << '\n';
 
    // reinterpreting
    double d = 0.1;
//  std::int64_t n = *reinterpret_cast<std::int64_t*>(&d); // aliasing violation
    std::int64_t n;
    std::memcpy(&n, &d, sizeof d); // OK
 
    std::cout << std::hexfloat << d << " is " << std::hex << n
              << " as an std::int64_t\n";
}