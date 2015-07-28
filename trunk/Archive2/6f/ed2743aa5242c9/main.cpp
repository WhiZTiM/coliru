#include <iostream>

struct B
{
    
    //static const int i;
};

struct D1 : public B
{
    static const int B::i = 0;
};

struct D2 : public B
{
    static const int B::i = 1;
};

int main()
{
    std::cout << D1::i << std::endl;
    std::cout << D2::i << std::endl;
    return 0;
}