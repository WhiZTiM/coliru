#include <iostream>

class myInt
{
  int val;

public:
  myInt(int);
  
  int get();
};

myInt::myInt(int i) : val(i) {}

int myInt::get()
{
  return val;
}

int main()
{
  myInt i = 5;
  std::cout << i.get();
  
  return 0;
}