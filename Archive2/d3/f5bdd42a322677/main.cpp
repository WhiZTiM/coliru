#include <iostream>
 
struct Point_2D {
  float x;
  float y;
};
 
int main() {
  //Define like any other type
  Point_2D point;
 
  //Use the dot before the name of the member to access
  point.x = 1.0f;
  point.y = 2.0f;
 
  //Remember, this will print as one line
  //because we don't use the \n newline or std::endl
  //for the first line!
  std::cout << "point.x: " << point.x << " | "
            << "point.y: " << point.y << std::endl;
 
  return 0;
}