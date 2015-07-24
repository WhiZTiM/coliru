struct T {
  template <typename Ty>
  Ty someTemplateFunc() { return Ty{}; }
};

template <typename Ty>
struct S {
  int f(const Ty &t) {
    return
      t.template someTemplateFunc<int>() + // ok
      t.someTemplateFunc<int>(); // not ok
    
  }
};

void f() {
  T t;
  S s;
  
  (void)s.f(t);
}

int main() { f(); }