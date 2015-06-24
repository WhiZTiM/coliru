
#include <iostream>
using namespace std;

class Outer {
  
  int a;
  class Inner {
      int a;
      friend class Outer; // required in C++98/03, but also in C++11, otherwise doesn't compile
      void change(Outer& o) {
          ++a;
          ++o.a;
      }
  };
  
  Inner inner;
  // friend class Inner; // required C++98/03, but automatically being friend in C++11 thus not required in C++11
  
public:
    Outer() {
        a = 1;
        inner.a = 3;
    }

    void print()const {
        cout << "a=" << a << ", inner.a=" << inner.a << endl;
    }
    
    void change() {
        inner.change(*this);
    }

};

int main() {
    Outer o;
    o.print();
    o.change();
    o.print();    
    return 1;
}