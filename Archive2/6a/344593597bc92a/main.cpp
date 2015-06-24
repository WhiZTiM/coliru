#include <iostream>
#include <mutex>

using namespace std;

class A;
class B {
public:
  B(A *_parent = nullptr) {
    parent = _parent;
  }
  A *parent;
};

class A {
public:
  std::mutex m;
  B *b;
  A() {
    b = new B(this);
  }
};

int main() {
  A a_obj;
  B *b = new B(&a_obj);
  b->parent->m.lock();
  return 0;
}