#include <iostream>
#include <memory>

int main()
{
  auto p_one = std::make_unique<int>();
  *p_one = 25;
  std::cout << *p_one << std::endl;
  
  {
      auto p_two = std::make_unique<int>();
      *p_two = 100;
      std::cout << *p_two << std::endl;
      
      p_one = std::move(p_two);
      
      std::cout << *p_one << std::endl;
  }   
  std::cout << *p_one << std::endl;
}
