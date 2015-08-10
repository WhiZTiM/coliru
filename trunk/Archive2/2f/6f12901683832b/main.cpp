#include <iostream>
 
struct Point_2D {
  float x;
  float y;
};
 
int main() {
  
  //You can use the brace syntax
  Point_2D point2 {3,4};
            
  std::cout << "point2.x: " << point2.x << " | "
            << "point2.y: " << point2.y << std::endl;
            
  point2 = {1, 2};
  
  std::cout << "point2.x: " << point2.x << " | "
            << "point2.y: " << point2.y << std::endl;
 
  return 0;
}