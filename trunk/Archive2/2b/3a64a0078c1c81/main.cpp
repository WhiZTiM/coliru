#include <iostream>
#include <limits>
#include <cstdint>

struct X 
{ 
    static const int i = std::numeric_limits<std::int32_t>::max(); 
};

int main()
{
    switch(std::numeric_limits<std::int32_t>::max()) { 
       case std::numeric_limits<std::int32_t>::max():
           std::cout << "this code works thanks to constexpr\n";
           break;
    }
    return EXIT_SUCCESS;
}