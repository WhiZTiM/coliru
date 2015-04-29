#include <iostream>
#include <string>
#include <vector>


// the foo action in these classes is to return the input value * 3

class COverrideBase
{
public:
  virtual ~COverrideBase() {}
  virtual int foo(int value)
  {
    std::cout << "  {COverrideBase::foo(int value)}"  << std::endl; // for demo only
    return value * 3;
  }

};

class COverrideDerived : public COverrideBase
{
public:
  //using COverrideBase::foo;
  // name hiding
  virtual double foo(double value)
  {
    std::cout << "  {COverrideDerived::foo(double value)}"  << std::endl;  // for demo only
    return value * 3;
  }


};

#include <typeinfo>
int main(int /*argc*/, char * /*argv*/ [])
{
  auto d2 = new COverrideDerived;
  std::cout << "2. after foo, value is:" << std::endl;
  std::cout << d2->foo(3) << std::endl;
  std::cout << "one might have expected COverrideDerived::foo(int value) to be called" << std::endl;
  std::cout << "typeid = " << typeid(d2->foo(3)).name() << std::endl;



  return 0;
}
