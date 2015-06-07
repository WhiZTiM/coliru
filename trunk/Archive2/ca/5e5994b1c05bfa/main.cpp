#include <iostream>
#include <exception>
#include <vector>

using namespace std;

class A {
public:
  A(int new_a) : a(new_a) { cout << 'a' << new_a << "() " << (std::uncaught_exception() ? "Unwinding" : "") << endl; }
  ~A() noexcept(false) {
    cout << "a" << a <<".~A() " << (std::uncaught_exception()?"Unwinding":"") << endl;
    
    if(a<=3)
      throw a;
  } 

  int a;
};

int main()
{
  cout << "Array" << endl << endl;

  try {
    A v[] = {1,2,3,4,5};
  } catch(...) { }

  cout << endl << "Local variables" << endl  << endl;

  try {
    A a1(1);
    A a2(2);
    A a3(3);
    A a4(4);
    A a5(5);
  } catch(...) { cout << "Recovered\n"; }

  cout << endl << "Vector" << endl  << endl;

  try {
    vector<A> v {1,2,3,4,5};
  } catch(...) { }
}