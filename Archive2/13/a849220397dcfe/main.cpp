#include <functional>
#include <iostream>

int main ()
{
  std::function<void (void)> f = [i=0] () mutable { std::cout << i++ << std::endl; };
  auto g = f;
  f ();
  f ();
  g ();
  g ();
}