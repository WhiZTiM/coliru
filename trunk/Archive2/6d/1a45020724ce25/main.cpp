#include <iostream>
#include <string>

    inline float aligned_size(float align, float size)
    {
        if (!align)
            return size;
            
        size += align;
        return size - std::remainder(size, align);
    }
    
int main()
{
    std::cout << aligned_size(10, -11);
}