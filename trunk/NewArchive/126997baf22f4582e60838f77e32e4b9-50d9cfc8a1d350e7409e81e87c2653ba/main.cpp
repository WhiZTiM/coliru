#include <iostream>


void* operator new(std::size_t)
{    
    std::cout << "Hello!" << std::endl;
}


void operator delete(void *)
{    
    std::cout << "Goodbye..." << std::endl;
}


int main()
{   
    delete new int;
}