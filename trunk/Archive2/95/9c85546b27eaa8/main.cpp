#include <iostream>
#include <functional>

void print_hello() {
  std::cout << "Hello world!" << std::endl;
}

void print_number(int const i) {
  std::cout << "number = " << i << std::endl;
}

class Trigger {
  std::function<void()> fp;
public:
  template<typename F, typename ...Args>
  Trigger(F f, Args... args) : fp(std::bind(f, args...)) { }
  void activate() { fp(); }
};

int main() {  
  Trigger trigger1(print_hello);
  trigger1.activate();
  Trigger trigger2(print_number, 123);
  trigger2.activate();
}