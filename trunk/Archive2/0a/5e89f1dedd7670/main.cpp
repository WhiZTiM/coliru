#include <iostream>
#include <string>

template <typename... Type>
struct sizeof_types {
    static const unsigned int size = sizeof...(Type);
};

int main()
{
  // Instead of sizeof(double) + sizeof(int) + sizeof(float) + sizeof(char)
  std::cout << sizeof_types<double,int,float,char>::size;
}
