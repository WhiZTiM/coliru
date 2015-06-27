template <typename T> struct Base {
  void DoThis(T x) {}
  static void DoThat(T x) {}
};

template <typename T> struct Derived : public Base<T> {
  void Work(T x) {
    DoThis(x);  // Invalid!
    DoThat(x);  // Invalid!
  }
};

int main()
{
    Derived<int>{}.Work(1);
}
