#include <iostream>
#include <sstream>
#include <cstdint>
int main()
{
  std::istringstream in("0xfff0 0xffff");
  int16_t i1=0, i2=0;
  in >> std::hex >> i1 >> i2;
  std::cout << i1 << std::endl << i2 << std::endl;
}