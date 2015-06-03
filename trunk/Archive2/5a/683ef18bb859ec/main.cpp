#include <iostream>

class S {
  int silly() {
    return 1;
  }
  
public:
  decltype(silly()) l;  
};

int main() {
  
}
