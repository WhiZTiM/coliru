#include <iostream>


template <typename T> class Parent { public:
  enum MyEnum { RED,GREEN,BLUE };
};
template <typename T> class Child : public Parent<T> { public:
  using typename Parent<T>::MyEnum;
  int foo() { return MyEnum::GREEN; }
};

int main() 
{ 
    Child<int> d; 
    d.foo(); 
}


