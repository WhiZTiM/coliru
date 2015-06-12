#include <iostream>

class myObj {
public:
 myObj() {}
 ~myObj() { std::cout << "dtor called" << std::endl; }
 myObj& someOtherOperation() {
  return *this;   
 }
};

int main() {
    auto& elementRef = myObj().someOtherOperation();
    {
        std::cout << "some stuff that uses elementRef" << std::endl;
    }  
}