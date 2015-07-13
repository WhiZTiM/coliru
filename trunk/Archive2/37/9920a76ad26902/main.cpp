#include <iostream>

struct test
{
    int val; 
    
    constexpr test(int val)
        : val(val)
    {
    }
};

template<int N>
struct CC
{
    double m[N]; 
};

int main()
{
    CC<test(6).val> k; 
    std::cout << std::end(k.m) - std::begin(k.m) << std::endl; 
    return 0;
}