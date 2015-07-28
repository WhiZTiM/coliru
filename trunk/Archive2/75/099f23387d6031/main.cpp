#include <iostream>

struct B
{
    
    static const int i;
};

struct D1 : public B
{
    const int B::i = 0;
};

struct D2 : public B
{
    const int B::i = 1;
};

int main()
{
    std::cout << "Hi !" << std::endl;
    return 0;
}