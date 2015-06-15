#include <iostream>

int main()
{
   int i = 0;
   i += ++i + ++i;
   std::cout << i << std::endl;
}