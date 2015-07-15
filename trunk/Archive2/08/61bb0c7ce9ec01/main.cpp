#include <iostream>
#include <string>
#include <vector>



int main()
{
  int* p_one = new int;
  {
      int* p_two = new int;
      p_one = p_two;        // Does this cause a memory leak with p_one's original address?
      std::cout << p_one << " == " << p_two << " ?\n";
  }   
}
