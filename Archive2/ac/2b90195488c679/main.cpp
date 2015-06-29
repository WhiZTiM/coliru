#include <future>
#include <iostream>
#include <thread>

struct S {
  bool b;
  
  S(bool b) : b(b) {
   std::cout << "Constructing" << std::endl;
  }
  
  S(const S &O) noexcept(false) {
    std::cout << "Copy construct" << std::endl;
    if (O.b) {
      throw S(false);
    }
  }
  
  S& operator=(const S &O) noexcept(false) {
    std::cout << "Copy assign" << std::endl;
    if (O.b) {
      throw S(false);
    }
    return *this;
  }

};

void f() {
  std::promise<int> prm;
  std::future<int> ftr = prm.get_future();
  
  std::thread([](std::promise<int> p) {
    std::cout << "Throwing from thread" << std::endl;
    try {
      throw S(true);
    } catch (S &) {
      std::cout << "Caught exception within thread" << std::endl;
      p.set_exception(std::current_exception());
    }
  }, std::move(prm)).detach();
  
  std::cout << "Getting the value (which may wait)" << std::endl;
  try {
    std::cout << ftr.get() << std::endl;
  } catch (S &s) {
    std::cout << "Caught exception thrown by get()" << std::endl;
  }
}

int main() {
  f();
}
