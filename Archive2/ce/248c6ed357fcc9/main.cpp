#include <iostream>

#if defined HAPPY
#define SAD "SAD"
#endif

int main()
{ 
    std::cout << SAD;
}