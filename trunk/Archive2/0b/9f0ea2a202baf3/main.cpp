#include <iostream>

class Base
{
public:
  Base() {}
  virtual ~Base() { std::cout << "Base::~Base()" << std::endl; }
  
  virtual void pure_virtual() = 0;
  virtual void regular_virtual() { std::cout << "Base::regular_virtual()" << std::endl; }
  void non_virtual() { std::cout << "Base::non_virtual()" << std::endl; }
};

class DerivedA : public Base
{
public:
  DerivedA() {}
  virtual ~DerivedA() { std::cout << "DerivedA::~DerivedA()" << std::endl; }
  
  inline void pure_virtual() { std::cout << "DerivedA::pure_virtual()" << std::endl; }
  
  void regular_virtual() { std::cout << "DerivedA::regular_virtual()" << std::endl; }
  
  void non_virtual() { std::cout << "DerivedA::non_virtual()" << std::endl; }
};

class LeafA : public DerivedA
{
public:
  LeafA() {}
  virtual ~LeafA() { std::cout << "LeafA::~LeafA()" << std::endl; }
  
  void regular_virtual() { std::cout << "LeafA::regular_virtual()" << std::endl; }
};

class DerivedB : public Base
{
public:
  DerivedB() {}
  ~DerivedB() { std::cout << "DerivedB::~DerivedB()" << std::endl; }
  
  void pure_virtual() { std::cout << "DerivedB::pure_virtual()" << std::endl; }
  
  virtual void non_virtual() { std::cout << "DerivedB::non_virtual()" << std::endl; }
};


int main()
{
    Base *one = new DerivedA();
    Base *two = new LeafA();
    Base *three = new DerivedB();
    
    std::cout << "Calling DerivedA::pure_virtual" << std::endl;
    one->pure_virtual();
    
    std::cout << "Calling DerivedB::pure_virtual" << std::endl;
    three->pure_virtual();
    
    std::cout << "-----------------------------------" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Calling DerivedA::regular_virtual" << std::endl;
    one->regular_virtual();
    std::cout << "Calling LeafA::regular_virtual" << std::endl;
    two->regular_virtual();
    
    std::cout << "-----------------------------------" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Calling DerivedA::non_virtual" << std::endl;
    one->non_virtual();
    std::cout << "Calling DerivedB::non_virtual" << std::endl;
    three->non_virtual();
    
    std::cout << "-----------------------------------" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Calling ~DerivedA" << std::endl;
    delete one;
    std::cout << std::endl;
    
    std::cout << "Calling ~LeafA" << std::endl;
    delete two;
    std::cout << std::endl;
    
    std::cout << "Calling ~DerivedB" << std::endl;
    delete three;
    std::cout << std::endl;
    
}