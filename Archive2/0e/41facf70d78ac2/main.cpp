#include <iostream>
#include <string>
#include <vector>

#include <iostream>

class foo
  {
public:
  int g (int x, int y) { return x + y ; }
  } ;

template<typename T>
using memberf_pointer = T; 

int main()
  {
  foo f ;
  auto mp = &foo::g;
  std::cout << (f.*mp) (5, 8) << std::endl ;
  }
