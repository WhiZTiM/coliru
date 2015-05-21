#include <iostream>

bool is_power_of_2(unsigned num) 
{
   return (num & - num) > (num - 1);
}

int main()
{
    std::cout << std::boolalpha << is_power_of_2(0);
}
