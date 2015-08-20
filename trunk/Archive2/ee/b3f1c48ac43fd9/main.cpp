#include <cstdio>

template <typename Derived>
class Base {
protected:
  Base(Derived *derived)
    : derived_(derived) {
  }
  
  ~Base() {
  }
  
private:
  Derived *const derived_;
  
public:
  void PrintFromDerived() {
    std::printf("%s\n", derived_->GetName());
  }
};


class Derived1 : public Base<Derived1> {
public:
  Derived1()
    : Base(this) {
  }
  
  char const* GetName() const {
    return "I'm Derived1!";
  }
};


class Derived2 : public Base<Derived2> {
public:
  Derived2()
    : Base(this) {
  }
  
  char const* GetName() const {
    return "I'm Derived2!";
  }
};


int main(int argc, char *argv[]) {
  Derived1 d1;
  Derived2 d2;
  d1.PrintFromDerived();
  d2.PrintFromDerived();
  return 0;
}