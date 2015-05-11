#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

mp::cpp_int fib(std::size_t n) {
  mp::cpp_int a = 1;
  mp::cpp_int b = 0;
  for (std::size_t i = 0; i != n; ++i) {
    a += b;
    std::swap(a, b);
  }
  return b;
}

int main() {
  std::cout << fib(2000) << "\n";
}
