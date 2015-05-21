#include <iostream>
#include <string>
#include <vector>

using namespace std;

class A {
  class PrivateType {  
  public:
     void bar() {
         cout << "Hello!" << endl;
     }
  };
public:  
  PrivateType foo() const {
      return PrivateType();
  }
};

int main(){    
    A a;
    
    // 1
    a.foo().bar();
    // 2
    auto b = a.foo();
    b.bar();
    
    // 3 - Fails at compile time
    // A::PrivateType c = a.foo();
    return 0;
}