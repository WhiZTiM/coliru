void foo() noexcept
{
  throw 1;
}

#include <iostream>

int main()
{
  try {
    foo();
  } catch(...) {
    std::cout << "Caught\n";
  }
  return 0;
}
