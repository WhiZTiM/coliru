#include <iostream>
 
int main()
{
  std::cout << std::boolalpha
            << true << '\n'
            << false << '\n'
            << std::noboolalpha
            << true << '\n'
            << false << '\n';
}