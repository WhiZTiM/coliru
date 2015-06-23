#include <iostream>
#include <string>
#include <vector>

int main()
{
    for(int i=0;i<5;i++)
    {
        auto f = [&]{std::cout << i << std::endl;};
        f();
    }
}
