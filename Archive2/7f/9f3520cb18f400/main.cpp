#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

bool foo(bool a)
{
    if(a)
    {
        return true;
    }
}
int main()
{
    std::cout << foo(true) << std::endl;
    std::cout << foo(false) << std::endl;
}
