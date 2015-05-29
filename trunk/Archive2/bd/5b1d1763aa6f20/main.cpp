#include <iostream>

int main()
{
    int x = 4 > 5 ? 0 : 1;
    
    int y;
    
    if(4 > 5)
        y = 0;
    else
        y = 1;
    
    std::cout << x << std::endl << y << std::endl;
}