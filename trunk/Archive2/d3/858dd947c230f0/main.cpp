#include <iostream>

auto genfunc (int start)
{
     int count=start;
     return [&count] {
         return count++;
     };
}

int main()
{
    std::cout << genfunc(10)() << std::endl;
}
