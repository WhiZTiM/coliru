// Example program
#include <iostream>
#include <string>

int** test()
{
    static int *hi[10];
    hi[0] = new int;
    hi[1] = new int;
    hi[2] = new int;
    hi[3] = new int;
    
    return hi;
}

void blank(int** hi)
{
    static int* u = new int[5];
    u[2] = 5;
    std::cout << u << std::endl;
    hi[0] = u;
}

int main()
{
  int** hi = test();
  std::cout << hi << std::endl;
  std::cout << hi[0] << std::endl;
  std::cout << hi[1] << std::endl;
  std::cout << hi[2] << std::endl;
  blank(hi);
  std::cout << hi << std::endl;
  std::cout << hi[0] << std::endl;
  std::cout << hi[1] << std::endl;
  std::cout << hi[2] << std::endl;
  std::cout << &hi[0][2] << std::endl;
}
