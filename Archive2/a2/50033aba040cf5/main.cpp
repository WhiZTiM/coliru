#define __ENABLE_EXPERIMENTAL_TADPOLE_OPERATORS 
#include <ios>
#include <iostream>
#include <istream>
 
int main()
{
   int n = 3;
   std::cout << "3 + 1 = " << -??-n  << std::endl;
   std::cout << "(3 - 1) * (3 + 1) = " << ??--n * -??-n << std::endl;
}