#include <utility>

struct A {
  A() {}
  A(int, int) {}
  A(const A&) = delete; // move only
  A(A&&) {};
};

std::pair<A, int> f()
{
  return {{18, 18}, 18}; // FAIL
}

std::pair<A, int> f2()
{
  return {A{18, 18}, 18}; // OK
}

int main()
{
}
