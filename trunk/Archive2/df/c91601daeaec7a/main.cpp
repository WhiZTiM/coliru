#include <iostream>

void function() {}

template<typename T> void univ(T&& p) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main() {

  void (&fun)() = function; // Reference to function
  univ(std::move(fun)); // According to http://stackoverflow.com/a/31125846/1938163, the result of std::move is a lvalue
  
}