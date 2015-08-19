#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

namespace mp = boost::multiprecision;

int main() {
  mp::uint128_t x = 18446744073709551615ULL;
  mp::uint128_t y = 18446744073709551615ULL;
  x *= y;
  std::cout << x << "\n";
}
