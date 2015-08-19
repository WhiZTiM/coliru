#include <iostream>

class ISomething
{
    virtual int a(int x) = 0;
    virtual int b(int x, int y) = 0;
public:
  virtual ~ISomething()
  { }
  int f(int x) {return a(x);} // (1)
  int f(int x, int y) {return b(x,y);} // (2)
};

class ASomething
  : public ISomething
{
  virtual int b(int x, int y) // (2)
  {
    return ISomething::f(x) + ISomething::f(y); // (3)
  }
};

class SomethingImpl
  : public ASomething
{
  virtual int a(int x) // (1)
  {
    return x+1;
  }
};

int main()
{
  SomethingImpl a;
  std::cout << a.f(10) << std::endl; // (1)
  std::cout << a.f(10,20) << std::endl; // (2)
  return 0;
}