#include <iostream>

struct Hello {
  Hello() {
    std::cerr << "Constructed at : " << this << std::endl;
  }

  Hello(Hello && ) { std::cerr << "Moved" << std::endl; }

  Hello(const Hello & ) { std::cerr << "copied" << std::endl; }

  ~Hello() {
    std::cerr << "Destructed at : " << this << std::endl;
  }

  double m_double;
};

Hello add(const Hello & h1, const Hello & h2) {
  Hello h = h1;
  h.m_double += h2.m_double;
  return std::move(h);
}
Hello add(Hello && h1, const Hello & h2) {
  h1.m_double += h2.m_double;
  return std::move(h1);

}

int main() {
  Hello h1;
  Hello h2;
  Hello h3 = add(add(add(add(Hello(), h1), h2), h1), h2);
}