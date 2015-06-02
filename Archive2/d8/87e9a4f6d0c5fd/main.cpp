#include <iostream>
#include <list>

class Animal {
public:
  Animal() {
  }
  virtual ~Animal() {
  }

  virtual void makeNoise() {
    std::cout << "This animal makes no sound." << std::endl;
  }
};

class Dog: public Animal {
public:
  virtual void makeNoise() {
    std::cout << "Wuf!" << std::endl;
  }
};

class Cat: public Animal {
public:
  virtual void makeNoise() {
    std::cout << "Maouw!" << std::endl;
  }
};

int main() {
  (*static_cast<Animal*>(new Dog())).makeNoise();
}