#include <iostream>

int main() {
  //Let's just use a variable for the radius.
  float c_radius = 1.2;
  std::cout << c_radius << std::endl;

  c_radius = 2.4;

  //Let's print out the area.
  float c_area = c_radius * c_radius * 3.1415;
  std::cout << c_area << std::endl;

  return 0;
}