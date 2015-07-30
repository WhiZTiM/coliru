#include <iostream>
#include <iomanip>

#define FILL_CHAR '#'
#define COUNT 8

int main()
{ 
    
    std::cout << "Count up\n";
    for (size_t i = 1; i <= COUNT; ++i)
    {
        std::cout << std::setfill(FILL_CHAR) << std::setw(i);
        std::cout << FILL_CHAR << std::endl;
    }
    
    std::cout << "Count down\n";
    for (size_t i=0; i<COUNT; ++i)
    {
        std::cout << std::setfill(FILL_CHAR) << std::setw(COUNT-i);
        std::cout << FILL_CHAR << std::endl;
    }
    
  return 0;
}