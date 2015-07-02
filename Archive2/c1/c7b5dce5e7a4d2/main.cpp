#include <iostream>

void function() {}

template<typename T> void univ(T&& p) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main() {

  void (&fun)() = function;
  univ(std::move(fun));
  
}