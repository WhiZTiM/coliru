#include <iostream>
using namespace std;

union intfloat {
  constexpr intfloat() :fl(0) { }
  uint32_t in;
  float fl;
};

constexpr uint32_t f(float x) {
  intfloat ifl;
  ifl.fl = x;
  return ifl.in;
}

int main() {
  cout << f(3.14159265359) << endl;
}
