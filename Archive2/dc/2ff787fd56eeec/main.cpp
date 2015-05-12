#include <stdio.h>
#include <string.h>
#include <new>
#include <iostream>

#include <memory>
#include <vector>
#include <type_traits>



int main()
{
   unsigned long long int a= 10;
   long long int b= -10;
   long long int c= a*long long int(b);
   std::cout << sizeof(a)<<"," << sizeof(b) << std::endl;
   std::cout << c << std::endl;
}
