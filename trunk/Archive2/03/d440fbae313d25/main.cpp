#include "test.h" 
#include <iostream>


// test.h   => http://coliru.stacked-crooked.com/a/f45484387123af75
// test.cpp => http://coliru.stacked-crooked.com/a/ff723f66745226c8


void externalized()
{
    // extern in test.h, explicitly instantiated in test.cpp
    std::cout << sum(1, 0) << std::endl;     
    std::cout << sum(2l, 0l) << std::endl;   
    std::cout << sum(3.0, 0.0) << std::endl;
}


void normal()
{   
    // not extern, not explicitly instantiated => default behavior
    std::cout << sum('a', 'b') << std::endl; 
}


extern template float sum(float, float);


void linker_error()
{
    // extern, but no explicit instantiation
    std::cout << sum(4.0f, 0.0f) << std::endl; 
}


int main() { }
