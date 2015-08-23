// overloading members on constness
#include <iostream>
using namespace std;

class MyClass {
    int x;
  public:
    MyClass(int val) : x(val) {}
    int& get() {return x;}
};

class MyClass2 {
    int x;
  public:
    MyClass2(int val) : x(val) {}
    int get() {return x;}
};
int main() {
  MyClass foo (10);
  MyClass2 bar (20);
  
 int a, b, c, d;
 
 a = foo.get();
 b = bar.get();
 c = foo.get();
 d = bar.get();
 
 a = 1;
 b = 2;
 c = 3;
 d = 4;
 
cout << "a: " << a << endl;
cout << "b: " << b << endl;
cout << "c: " << c << endl;
cout << "d: " << d << endl;

  return 0;
}