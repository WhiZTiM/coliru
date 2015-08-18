#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>
#include <sstream>
#include <type_traits>
#include <memory>

struct plus_impl {
  template<class Self, std::enable_if_t<std::is_class<std::decay_t<Self>>{}>* = nullptr>
  friend std::decay_t<Self> operator+(int num, Self&& self) {
    auto tmp = std::forward<Self>(self); // perfect forward a copy
    tmp += num; // delegate to +=
    return tmp; // elide return value
  }
  template<class Self, std::enable_if_t<std::is_class<std::decay_t<Self>>{}>* = nullptr>
  friend std::decay_t<Self> operator+(Self&& self, int num) {
    return num + std::forward<Self>(self); // DRY principle
  }
};

template<class T>
class MyClass :public plus_impl {
public:
  MyClass& operator+=(int num){
      std::cout << "+=" << num << "\n";
      return *this;
  } // do actual work here
};

int main() {
    MyClass<int> bob;
    bob += 1;
    bob + 2;
    3 + bob;
}