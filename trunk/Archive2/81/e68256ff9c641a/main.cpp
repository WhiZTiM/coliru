#include <iostream>

struct Car
  {
  Car() { std::cout << "Car::ctor"<< std::endl; };
  Car(const Car&) { std::cout <<"Car::cctor" << std::endl; }
  Car(Car&&) { std::cout << "Car::mctor" << std::endl; }
  ~Car() { std::cout <<"Car::dtor" << std::endl; }
  };

struct DerivedCar : public Car
  {
  DerivedCar() : Car(Car{}) { std::cout << "DerivedCar::ctor" << std::endl; }
  DerivedCar(const DerivedCar&) { std::cout <<"DerivedCar::cctor" << std::endl; }
  };

int main()
  {
  DerivedCar dc;
  }