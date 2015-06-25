#include <iostream>

class one{
public:
  void x() { std::cout << "x\n"; }
  void y() { std::cout << "y\n"; }
};
typedef void(one::*PF)(void);

class two :public one{
public:
  virtual PF getOneMethodPointer()
  {
      return &one::x;
  }
};

int main()
{
    two t;
    PF f = t.getOneMethodPointer();
    (t.*f)();
}