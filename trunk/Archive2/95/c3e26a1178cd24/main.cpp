#include <type_traits>

template <int answer> struct this_is_false : std::false_type {};

template <int answer> struct Hitchhiker {
  static_assert(this_is_false<answer>::value, "Invalid answer");
};

// template <> struct Hitchhiker<42> {};

int main()
{

}
