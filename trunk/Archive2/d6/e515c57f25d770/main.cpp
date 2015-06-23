#include <type_traits>

// Helper trait that either specifies an enumeration's underlying
// type, or the given template parameter type.
template <typename T, bool = std::is_enum<T>::value>
struct UnderlyingTrait{};

template <typename T>
struct UnderlyingTrait<T, true> {
  using type = typename std::underlying_type<T>::type;
};

template <typename T>
struct UnderlyingTrait<T, false> {
  using type = T;
};

// Class type that requires the template parameter type to either be
// an integral type, or an enumeration type.
template <typename T, bool = std::is_enum<T>::value || std::is_integral<T>::value>
struct S {};

template <typename T>
struct S<T, true> {
  // Determine the underlying type of the template parameter.
  using underlying = typename UnderlyingTrait<T>::type;
};

//////////////// Testing code from here down //////////////////
enum E1 {};
enum E2 : short {};
class C {};

template <typename Ty>
class sfinaed_out {
  typedef char yes[1];
  typedef char no[2];

  template <typename Inner>
  static yes& test(Inner *, typename S<Inner>::underlying * = nullptr);

  template <typename>
  static no& test(...);

public:
  static const bool value = sizeof(test<Ty>(nullptr)) == sizeof(no); // We are testing that the object does *not* exist
};

void f() {
  static_assert(std::is_same<S<unsigned>::underlying, unsigned>::value, "unsigned");
  static_assert(std::is_same<S<E1>::underlying, unsigned int>::value, "unscoped enum unsigned int"); // Compiler-dependent
  static_assert(std::is_same<S<E2>::underlying, short>::value, "scoped enum short");
  static_assert(!std::is_same<S<short>::underlying, int>::value, "Underlying type should be short instead of int");
  static_assert(sfinaed_out<float>::value, "float");
  static_assert(sfinaed_out<C>::value, "C");
  static_assert(!sfinaed_out<int>::value, "int should not be sfinaed out");
}

int main() {
  f();
}
