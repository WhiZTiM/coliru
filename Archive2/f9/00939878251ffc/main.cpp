#include <vector>
#include <string>
#include <iostream>

#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>

using namespace ranges;

template <std::size_t N>
struct get_n {
  template <typename T>
  auto operator()(T&& t) const ->
    decltype(std::get<N>(std::forward<T>(t))) {
      return std::get<N>(std::forward<T>(t));
  }
};

namespace ranges {
template <class T, class U>
std::ostream& operator << (std::ostream& os, common_pair<T, U> const& p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
}

int main() {
  std::vector<std::string> names {"john", "bob", "alice"};
  std::vector<int>         ages  {32,     19,    35};

  auto zipped = view::zip(names, ages);
  std::cout << "Before: Names: " << view::all(names) << '\n'
            << "         Ages: " << view::all(ages) << '\n'
            << "       Zipped: " << zipped << '\n';
  sort(zipped, less{}, get_n<1>{});
  std::cout << " After: Names: " << view::all(names) << '\n'
            << "         Ages: " << view::all(ages) << '\n'
            << "       Zipped: " << zipped << '\n';
}
