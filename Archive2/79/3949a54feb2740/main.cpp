#include <iostream>

struct Car
  {
  static unsigned int constructor_count;
  Car() { std::cout << "Car::ctor"<< std::endl; ++constructor_count; };
  Car(const Car&) { std::cout <<"Car::copy ctor" << std::endl; ++constructor_count; };
  Car(Car&&) { std::cout << "Car::move ctor" << std::endl; ++constructor_count; };
  ~Car() { std::cout <<"Car::dtor" << std::endl; }
  };

unsigned int Car::constructor_count = 0;

struct DerivedCar : public Car
  {
  DerivedCar() : Car(Car{}) { std::cout << "DerivedCar::ctor" << std::endl; }
  DerivedCar(const DerivedCar&) { std::cout <<"DerivedCar::copy ctor" << std::endl; }
  };

void print_car_constructor_count()
  {
  std::cout << "Car constructor count = " << Car::constructor_count << std::endl;       
  }
  
void reset_car_constructor_count()
  {
  Car::constructor_count = 0u;
  }

int main()
  {
      
  print_car_constructor_count();
  Car car1;
  print_car_constructor_count();

  reset_car_constructor_count();
  std::cout << "--------------------" <<  std::endl;
  
        
  print_car_constructor_count();
  Car car2 = car1;
  print_car_constructor_count();

  reset_car_constructor_count();
  std::cout << "--------------------" <<  std::endl;
        
  print_car_constructor_count();
  Car car3 = Car{};
  print_car_constructor_count();

  reset_car_constructor_count();
  std::cout << "--------------------" <<  std::endl;
  
  print_car_constructor_count();
  Car car4{Car{car3}};
  print_car_constructor_count();

  reset_car_constructor_count();
  std::cout << "--------------------" <<  std::endl;

  DerivedCar dc;
  }