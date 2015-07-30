template<int N>
struct Foo {
  constexpr int Bar() const { return N; }
};

template<int N>
constexpr int ByValue(Foo<N> f) {
  constexpr int i = f.Bar();
  (void) i;
  return f.Bar();
}

template<int N>
constexpr int ByReference(const Foo<N> &f) {
  constexpr int i = f.Bar();
  (void) i;
  return f.Bar();
}

int main(int, const char **) {
  constexpr int a = ByValue(Foo<1>{});
  constexpr int b = ByReference(Foo<1>{});
  (void) a;
  (void) b;
  
  return 0;
}
