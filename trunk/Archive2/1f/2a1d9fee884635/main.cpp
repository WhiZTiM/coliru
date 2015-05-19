#include <iostream>
#include <string>
#include <vector>

template<typename T>
T Twice(T data)
{
   return data * 2;
}


int main()
{
  std::cout << Twice(10) << std::endl;
  std::cout << Twice(3.14) << std::endl;
  std::cout << Twice( Twice(55) ) << std::endl;
}
