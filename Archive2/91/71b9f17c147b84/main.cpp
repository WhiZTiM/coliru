struct C {
  template <typename T>
  void fun() { }
  
  static constexpr const auto fun_int = &C::fun<int>;
};

int main() {
    C c;
    (c.*C::fun_int)();
}