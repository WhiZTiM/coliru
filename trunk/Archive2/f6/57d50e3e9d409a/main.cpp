#include <iostream>

struct test
{
    int val; 
    
    constexpr test(int val)
        : val(val)
    {
    }
};

int main()
{
    test a(1); 
    ++a.val; 
    std::cout << a.val << std::endl;
    return 0;
}