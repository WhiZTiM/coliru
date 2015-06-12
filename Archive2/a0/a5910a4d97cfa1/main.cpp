#include <type_traits>
#include <iostream>

auto func() 
{
    struct {
        int res1;
        std::string res2;
    } result{ 1, "putin huylo"};
    return result; 
}


int main()
{
    auto r = func();
    std::cout << r.res2 << std::endl;
}