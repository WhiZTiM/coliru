#include <iostream>
#include <tuple>

class Foo {
 private:
  std::tuple<int, float> data_;
  int &GetBar() { return std::get<0>(data_); };
  int const &GetBar() const { return std::get<0>(data_); };
  float &GetBaz() { return std::get<1>(data_); };
  float const &GetBaz() const { return std::get<1>(data_); };

 public:  
  Foo(int i, float f) : data_{i, f} {}
  float GetSum() { return GetBar() + GetBaz(); }
  float GetProduct() { return GetBar() * GetBaz(); }
};

class Bla {
 private:
  struct Bar { int value; };
  struct Baz { float value; };
  std::tuple<Bar, Baz> data_;

 public:  
  Bla(int i, float f) : data_{{i}, {f}} {}
  float GetSum() { return std::get<Bar>(data_).value + std::get<Baz>(data_).value; }
  float GetProduct() { return std::get<Bar>(data_).value * std::get<Baz>(data_).value; }
};

int main() {
  Foo foo{10, 22};
  std::cout << foo.GetSum() << "\n";
  std::cout << foo.GetProduct() << "\n";

  Bla bla{10, 22};
  std::cout << bla.GetSum() << "\n";
  std::cout << bla.GetProduct() << "\n";
}