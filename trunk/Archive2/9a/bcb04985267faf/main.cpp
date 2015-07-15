#include <iostream>

//Classes are defined using curly braces (don't
//forget the parentheses!)
class Circle {

//Classes have this thing called privacy control.
//We use it to prevent ourselves from using variables
//based on whether we use it inside or outside a class.
public:

  //This is called a constructor function.
  //It always has the same name as the class.
  Circle(float r) :
    radius(r) {
    std::cout << "Circle constructed." << std::endl;
  }

  //This is a destructor function.
  //It is called when an object created from this
  //"class-type" goes out of SCOPE.
  ~Circle() {
	std::cout << "Circle destroyed." << std::endl;
  }

  //"get_NAME/set_NAME" is a common function name
  //This is part of what we call encapsulation.
  void set_radius(float r) {
	radius = r;
  }

  float get_radius() {
	return radius;
  }

  //Here's an example of how we can transform our data
  //to find something useful:
  //area of circle = [pi (the math constant) * r * r]
  float get_area() {
	return (3.1415 * radius * radius);
  }
private:
  float radius;
};

int main() {
  //Create an object or instance of a class
  //using the class name as a type.
  //This is when the CONSTRUCTOR is called.
  Circle c(1.2f);

  //See how we use the dot (.) to "reference"
  //or use the function that belongs to the class?
  std::cout << c.get_radius() << std::endl;

  //What if we want to change the radius?
  c.set_radius(2.4f);
  
  //Let's print out the area.
  std::cout << c.get_area() << std::endl;

  return 0;
} //This is about where the DESTRUCTOR is called.
//This is because the end of main() is the end of
//the "scope" of the variable.

//See? Even main() obeys scope rules!