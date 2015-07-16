#include <iostream>
#include <string>
#include <vector>



int main()
{
  int* p_one = new int;
  *p_one = 25;
  std::cout << *p_one << std::endl;
  
  {
      int* p_two = new int;
      *p_two = 100;
      std::cout << *p_two << std::endl;
      
      if(!p_one) delete p_one;    // Is this correct for stoping memory leak?
      p_one = p_two;                        // Delete p_one before asigning p_two's address.
      
      std::cout << *p_one << std::endl;     // p_one now has the location set aside from p_two's "new"
  }   
  std::cout << *p_one << std::endl;
  delete p_one;
}
