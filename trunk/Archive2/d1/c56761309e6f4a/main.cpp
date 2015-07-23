struct S {
  int x;
  void f() {
    auto l = [&] { return x; };
  }
};
int main() {
}
