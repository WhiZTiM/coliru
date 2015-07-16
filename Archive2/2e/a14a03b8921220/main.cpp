#include <iostream>
#include <string>
#include <vector>


void pointer_return(int *value)
{
    int* p_two = new int;
    *p_two = 25;
    value = p_two;
}


int main()
{
  int* p_one = new int;
  pointer_return(p_one);
  std::cout << *p_one; 
}
