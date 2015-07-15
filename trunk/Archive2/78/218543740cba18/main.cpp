#include <functional>
#include <iostream>

struct mav {};
struct msg {};

#ifdef DEBUG
#error DEBUG is defined
#endif

#ifdef _DEBUG
#error _DEBUG is defined
#endif

#ifdef ENABLE_ASSERTS
#error ENABLE_ASSERTS is defined
#endif

int main()
{   
    std::cout << "Hello World" << std::endl;
    
    return 0;
}