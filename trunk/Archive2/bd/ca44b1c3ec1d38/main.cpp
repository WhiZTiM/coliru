#include <iostream>
#include <string>
#include <vector>

#include <iostream>

class foo
  {
public:
  int g (int x, int y) { return x + y ; }
  } ;

template<typename T, typename...Args>
using memberf_pointer = int (T::*)(Args&&...); 

int main()
  {
  foo f ;
  memberf_pointer<foo> mp = &foo::g ;
  std::cout << (f.*mp) (5, 8) << std::endl ;
  }
