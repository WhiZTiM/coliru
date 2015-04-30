#include <iostream>

enum { i = 1 };

class X {
#ifdef GOOD
  enum { i = 2 };
#endif
  char v[i];
#ifdef BAD
  enum { i = 2 };
#endif

public:
  void print() const { std::cout << sizeof(v) << std::endl; }
  
};

int main() {
  std::cout << 
#if defined(GOOD)
  "good"
#elif defined(BAD)
  "bad"
#endif
  << std::endl;
  X x;
  x.print();
}