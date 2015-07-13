#include <string>
#include <iostream>
#include <memory>
using namespace std;

class Pointed{
public:
    Pointed(){std::cout << "Construction\n";}
    ~Pointed(){std::cout << "Destruction\n";}
};

class A1 {

private:
  Pointed * p_str;

public:
  A1() : p_str(new Pointed())
  {
  }

  virtual ~A1() {
    delete p_str;
  }
};

class B : public A1 {
public:
  B() {
      throw "B constructor";
  }

  virtual ~B() override {
  }

  virtual void Test() {
    cout << "B::Test()" << endl;
  }
};

class A2 {

private:
  std::unique_ptr<Pointed> p_str;

public:
  A2() : p_str(make_unique<Pointed>()){}
  virtual ~A2() {}

};


class C : public A2 {
public:
  C() {
      throw "C constructor";
  }

  virtual ~C() override {
  }

  virtual void Test() {
    cout << "C::Test()" << endl;
  }
};

int main(int, char**)
{
    try{
  B b;
    }
    catch(...){std::cout << "Exception thrown for b\n";}
    try{
  C c;
    }
    catch(...){std::cout << "Exception thrown for c\n";}

    return 0;
}