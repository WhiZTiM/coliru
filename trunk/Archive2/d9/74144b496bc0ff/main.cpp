#include <array>
#include <utility>
#include <iostream>

template <typename T, T... Ints>
constexpr std::array<T, sizeof...(Ints)> iota_array_init(std::integer_sequence<T, Ints...> ) {
  return {Ints...};
}

template <typename T, size_t N>
constexpr auto iota_array()
{
    return iota_array_init(std::make_integer_sequence<T, N>{});
}

constexpr size_t E = 256;
static const std::array<unsigned, E> X = iota_array<unsigned, E>();

struct whatever {
  char c;
  bool b;
  int i;
  long l;
  long long ll;
  union {
   short s;
   wchar_t w;
   char *pc;
  } u;
} we[7];


int main() {
  auto counter = 0;
  for (auto&& i : X) {
    if (counter == 32) {
      counter = 0;
      std::cout << '\n';
    } else {
      std::cout << ' ';
      ++counter;
    }
    std::cout << i;
  }
  std::cout << '\n' << sizeof(we) << '\t' << sizeof(whatever);
}
