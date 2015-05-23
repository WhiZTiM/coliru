#include <iostream>

struct Foo {
  int* p;
  explicit Foo(int* p) : p(p) { *p += 100; }
  Foo(const Foo& other) : p(other.p) { *p += 10; }
  Foo(Foo&& other) : p(other.p) { *p += 1; }
};

int x = 0;
Foo foo((Foo(&x)));

int main() {
    std::cout << x << '\n';
}
