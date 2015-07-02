/*
#include <stdio.h>
#include <vector>

class Foo {
 public:
  Foo() {
    printf("From Foo.\n");
  }

  Foo& operator = (const Foo& foo) {
    printf("From Assignment Foo.\n");
    return *this;
  }

  Foo& operator = (Foo&& foo) {
    printf("From Move Assignment Foo.\n");
    return *this;
  }


  Foo(Foo&& foo) {
    printf("From Move Foo.\n");
  }

  Foo(const Foo& foo) {
    printf("From Copy Foo. this=%p Other=%p\n", this, &foo);
  }

  void Log() const {
    printf("From Foo::Log() %p\n", this);
  }
};

int main(int argc, char* argv[]) {
  const std::vector<Foo> a { Foo() };
  std::vector<Foo> b;
  a[0].Log();
  b = std::move(a);
  b[0].Log();
}

*/

// move algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::move (ranges)
#include <utility>      // std::move (objects)
#include <vector>       // std::vector
#include <string>       // std::string

int main () {
  std::vector<std::string> foo = {"air","water","fire","earth"};
  std::vector<std::string> bar (4);

  // moving ranges:
  std::cout << "Moving ranges...\n";
  std::move ( foo.begin(), foo.begin()+4, bar.begin() );

  std::cout << "foo contains " << foo.size() << " elements:";
  std::cout << " (each in an unspecified but valid state)";
  std::cout << '\n';

  std::cout << "bar contains " << bar.size() << " elements:";
  for (std::string& x: bar) std::cout << " [" << x << "]";
  std::cout << '\n';

  // moving container:
  std::cout << "Moving container...\n";
  foo = std::move (bar);

  std::cout << "foo contains " << foo.size() << " elements:";
  for (std::string& x: foo) std::cout << " [" << x << "]";
  std::cout << '\n';

  std::cout << "bar is in an unspecified but valid state";
  std::cout << '\n';

  return 0;
}