#include <iostream>

class A
{
  public:
  
  void test() const { std::cout << "test" << std::endl; }
  
  template<typename T = void>
  void test() const { std::cout << "test<>" << std::endl; }
};

int main()
{
  A a;
  a.test();
  a.test<>();
}