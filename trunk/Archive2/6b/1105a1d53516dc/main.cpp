#include <iostream>
#include <unordered_map>

struct Foo {
  Foo() { std::cout << "Foo() called" << std::endl; }
  Foo(Foo const &other) { std::cout << "Foo(Foo const &other) called" << std::endl; }
  Foo(Foo &&other) { std::cout << "Foo(Foo &&other) called" << std::endl; }
  int i = 0;
};

bool operator==(Foo const &lhs, Foo const &rhs) {
  return lhs.i == rhs.i;
}

void hash_combine(std::size_t& seed, const Foo& v) {
    std::hash<int> hasher;
    seed ^= hasher(v.i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

struct CustomHash {
  std::size_t operator()(Foo const& v) const  {
    std::size_t res = 0;
    hash_combine(res, v);
    return res;
  }
};

int main() {
  std::unordered_map<Foo, int, CustomHash> fmap;
  
  Foo a;
  a.i = 100;
  fmap[a] = 100;
  fmap[Foo()] = 1;

}