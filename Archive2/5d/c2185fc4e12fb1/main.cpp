#include <iostream>
#include <string>
#include <sstream>

int main()
{
    auto a = 42;
    auto str = std::string("Lalala");
    
#if 0
    char buf[20];
    std::istringstream stream("Hello, there!");
    stream.read(buf, sizeof buf);
    // Conversion from std::streamsize to size_t
    size_t bytes_extracted = stream.gcount();
    std::cout << "Characters extracted " << bytes_extracted << '\n';
#endif
}