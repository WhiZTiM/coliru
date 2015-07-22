#include <iostream>
#include <cstdlib>
#include <ctime>

bool printIf(int line, bool val)
{
  std::cout << "Line: " << line << std::endl;
  return val;
}

#define IF(x) if( x ? printIf(__LINE__, true) : printIf(__LINE__, false) )

int main()
{
  srand(time(NULL));
  //int val;
  //IF (val = rand())
  IF(int val = rand())
  {
    std::cout << "val = " << val << std::endl;
  }
}