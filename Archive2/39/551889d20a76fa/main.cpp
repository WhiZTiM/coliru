struct T {
  template <typename Ty>
  Ty someTemplateFunc() { return Ty{}; }
};

template <typename Ty>
struct S {
  int f(const Ty &t) {
    return t.someTemplateFunc<int>();
  }
};

void f() {
  T t;
  S s;
  
  (void)s.f(t);
}

int main() { f(); }