#include <chrono>
#include <iostream>

void f() {
  using namespace std::chrono;
  time_point<std::chrono::system_clock> tp(duration<unsigned long long>::max());
  duration<unsigned long long> o;
  o++;

  std::cout << tp.time_since_epoch().count() << std::endl;

  tp += o;

  std::cout << tp.time_since_epoch().count() << std::endl;
}

int main() {
  f();
}
