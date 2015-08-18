#include <iostream>

enum A
{
    B
};

bool test()
{
    return true;
}

int main()
{
    
    if (test(), A::B)
    {
        std::cout << "Hello" << std::endl;
    }
    return 0;
}