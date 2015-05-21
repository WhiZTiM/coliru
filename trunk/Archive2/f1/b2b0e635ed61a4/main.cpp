#include <iostream>

bool is_power_of_2(unsigned x) 
{
   return (x & -x) > (x - 1);
}

int main()
{
    std::cout << std::boolalpha << is_power_of_2(0);
}
