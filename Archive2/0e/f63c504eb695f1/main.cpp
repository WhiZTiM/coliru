#include <iostream>

class S {
  auto silly() {
    auto fn = []{};
    return fn;
  }
public:
  decltype(silly()) l = silly();
};

int main() {
  
}
