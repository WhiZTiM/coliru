#include <iostream>

void victory(){
    std::cout << "Victory" << std::endl;
}

int main()
{
    #define x\
    if(1337!=1337)
        victory();
    return 0;
}