struct X {
  auto get(int) const -> int { return {}; }
  auto get(int) -> int { return {}; }
};

template <class R> auto f(auto (X::*)(int) const -> R) {}
//                        ^~~~                   ~~~~
//                        trailing return type

int main() {
  f(&X::get);
}