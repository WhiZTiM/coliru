#include "test.h"
#include <iostream>


// enabling this line causes linker error
//extern template float sum(float, float);


int main()
{
    std::cout << sum(3, 4) << std::endl;     // extern in test.h, explicitly instantiated in test.cpp
    std::cout << sum(3l, 4l) << std::endl;   // extern in test.h, explicitly instantiated in test.cpp
    std::cout << sum(3.0, 4.0) << std::endl; // extern in test.h explicitly instantiated in test.cpp

    
    // T=float is not explicitly instantiated in test.cpp
    // so instantiation happens here unless the commented out extern above is enabled
    std::cout << sum(3.0f, 4.0f) << std::endl; 
    
}
