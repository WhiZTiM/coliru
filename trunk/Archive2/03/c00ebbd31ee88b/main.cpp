#include <iostream>
#include <type_traits>
 
struct Point_2D {
  
    
  float x;
  float y;

  
};

struct Point_3D : public Point_2D {
  float z;  
};
 
int main() {
  
  //You can use the brace syntax
  void* my = malloc(20);
    std::cout << sizeof(my);
 
  return 0;
}