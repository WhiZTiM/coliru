#include <cstring>

int main()
{   
    int length = 0;
    
    size_t n;
    
    n = static_cast<size_t>(length) ;
    
    n = static_cast<size_t>(length) * sizeof(int) ;
    
    n = sizeof(int) * static_cast<long unsigned int>(length) ;
    
    n = sizeof(int) * static_cast<unsigned int>(length) ;
    
    n = sizeof(int) * static_cast<size_t>(length) ;
}