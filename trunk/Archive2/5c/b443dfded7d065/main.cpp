#include <string>
#include <iostream>

int main() 
{
   std::string s = "123";
   int i = std::stoi(s);
   std::cout << i << '\n';
   return 0;
}