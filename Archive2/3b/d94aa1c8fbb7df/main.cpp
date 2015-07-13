#include <iostream>
#include <memory>
using namespace std;

class Pointed {
public:
  Pointed() { std::cout << "Pointed()\n"; }
  ~Pointed() { std::cout << "~Pointed()\n"; }
};

class A1 {
private:
  Pointed * p_str;

public:
  A1() : p_str(new Pointed()) {
    cout << "A1()\n";
    throw "A1 constructor";
  }

  virtual ~A1() {
    cout << "~A1()\n";
    delete p_str;
  }
};

class B1 : public A1 {
public:
  B1() {
    throw "B constructor";
  }

  virtual ~B1() override {
    cout << "~B1()\n";
  }

  virtual void Test() {
    cout << "B1::Test()" << endl;
  }
};

class A2 {
private:
  std::unique_ptr<Pointed> p_str;

public:
  A2() : p_str(make_unique<Pointed>()) {
    cout << "A2()\n";
    throw "A2 constructor";
  }
  
  virtual ~A2() {
    cout << "~A2()\n";
  }
};


class B2 : public A2 {
public:
  B2() {
    cout << "B2()\n";
    throw "B2 constructor";
  }

  virtual ~B2() override {
    cout << "~B2()\n";
  }

  virtual void Test() {
    cout << "B2::Test()" << endl;
  }
};

int main(int, char**) {
  cout << "B1::A1 (raw pointers)\n";

  try {
    B1 b1;
  }
  catch (...) {
    cout << "Exception thrown for B1\n";
  }

  cout << "\nB2::A2 (unique pointers)\n";

  try {
    B2 b2;
  }
  catch (...) {
    cout << "Exception thrown for b2\n";
  }

  cin.get();

  return 0;
}
