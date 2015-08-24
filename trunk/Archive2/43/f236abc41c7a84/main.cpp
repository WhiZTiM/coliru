template <typename T>
struct A;

template <typename T>
constexpr A<T> f();

template <typename T>
struct A {
  friend constexpr A f<T>();
 private:
  constexpr A(){}
};

template <typename T>
constexpr A<T> f() { return {}; }

int main() {
  constexpr auto a  = f<void>();

}

