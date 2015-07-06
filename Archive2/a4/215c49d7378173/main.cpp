#include <iostream>

void f(int* decay)
{
  std::cout << sizeof(decay) << '\n';
}
int main()
{
  int bla[5] = {};
  std::cout << sizeof(bla) << '\n';
  f(bla);
}