#include <utility>

struct A {
  A() {}
  A(int, int) {}
  A(const A&) = delete; // move only
  A(A&&) {};
};

struct K
{
    A a;
    int k;
};

K f()
{
  return {{18, 18}, 18}; // FAIL
}

K f2()
{
  return {A{18, 18}, 18}; // OK
}

int main()
{
    K k1 = f();
    K k2 = f2();
}
