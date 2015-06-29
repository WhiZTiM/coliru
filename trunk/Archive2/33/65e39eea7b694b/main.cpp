#include <functional>
#include <iostream>

template <typename T> class ref {
private:
  T &val;

public:
  ref(T &r) : val(r) {}

  template <typename R> ref<T> &operator=(R const &rhs) {
    val = rhs;
    return *this;
  }

  // BINOP_TY(+);
  template <typename L, typename R>
  friend auto operator+(L lhs, ref<R> rhs) -> decltype((lhs) + (rhs.val));

  template <typename L, typename R>
  friend auto operator+(ref<L> lhs, R rhs) -> decltype((lhs.val) + (rhs));

  template <typename L, typename R>
  friend auto operator+(ref<L> lhs, ref<R> rhs)
      -> decltype((lhs.val) + (rhs.val));

  // BINOP_TY(*);
  template <typename L, typename R>
  friend auto operator*(L lhs, ref<R> rhs) -> decltype((lhs) * (rhs.val));

  template <typename L, typename R>
  friend auto operator*(ref<L> lhs, R rhs) -> decltype((lhs.val) * (rhs));

  template <typename L, typename R>
  friend auto operator*(ref<L> lhs, ref<R> rhs)
      -> decltype((lhs.val) * (rhs.val));
};

// BINOP(+);
template <typename L, typename R>
auto operator+(L lhs, ref<R> rhs) -> decltype((lhs) + (rhs.val)) {
  return lhs + rhs.val;
}

template <typename L, typename R>
auto operator+(ref<L> lhs, R rhs) -> decltype((lhs.val) + (rhs)) {
  return lhs.val + rhs;
}

template <typename L, typename R>
auto operator+(ref<L> lhs, ref<R> rhs) -> decltype((lhs.val) + (rhs.val)) {
  return lhs.val + rhs.val;
}

// BINOP(*);
template <typename L, typename R>
auto operator*(L lhs, ref<R> rhs) -> decltype((lhs) * (rhs.val)) {
  return lhs * rhs.val;
}

template <typename L, typename R>
auto operator*(ref<L> lhs, R rhs) -> decltype((lhs.val) * (rhs)) {
  return lhs.val * rhs;
}

template <typename L, typename R>
auto operator*(ref<L> lhs, ref<R> rhs) -> decltype((lhs.val) * (rhs.val)) {
  return lhs.val * rhs.val;
}

// Works.
void plus(ref<int> r, int i) {
  r = r + i;
}

// Fails.
void mult(ref<int> r, int i) {
  r = r * i;
}

int main()
{
  int i = 5;
  ref<int> r = i;
  int j = 42;
  r = r * j;
  std::cout << 42 << std::endl;
}
