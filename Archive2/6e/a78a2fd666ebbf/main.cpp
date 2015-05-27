#define __ENABLE_EXPERIMENTAL_TADPOLE_OPERATORS 
#include <ios>
#include <iostream>
#include <istream>
 
int main()
{
   int _ = 3;
   std::cout << "3 + 1 = " << -??-+_  << std::endl;
   std::cout << "(3 - 1) * (3 + 1) = " << +??--+_*-??-+_ << std::endl;
}