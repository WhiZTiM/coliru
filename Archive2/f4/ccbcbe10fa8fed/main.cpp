#include <iostream>

auto bar = [i = 1] () mutable { return i++; };

int main ()
{
  for (size_t i = 0; i < 3; ++i)
  {
      std::cout << bar () << std::endl;
  }
}