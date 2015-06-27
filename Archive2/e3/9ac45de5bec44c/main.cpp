#include <type_traits>
#include <utility>
#include <array>

template<typename I>
class encrypted_string;

template<std::size_t... I>
class encrypted_string<std::index_sequence<I...>>
{
 private:
  std::array<char, sizeof...(I)> buf;

  static constexpr char encrypt(char c) { return c ^ 0x41; }

 public:
  constexpr encrypted_string(const char* str)
  : buf { encrypt(str[I])... } { }
};

#define enc(str) encrypted_string<std::make_index_sequence<sizeof(str)>>(str)

int main()
{
  // Ensures compile time evaluation
  constexpr auto s = enc("Test");

  return 0;
}
