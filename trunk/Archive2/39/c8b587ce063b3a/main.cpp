#include <iostream>
#include <vector>
#include <string>

enum class demo_initialize { a = 1, b, c, d };

class Base {
  public:
    Base(demo_initialize initialize) : mInitialize(initialize) {}

  protected:
    demo_initialize mInitialize;
};

template <typename T>
class Derived : public Base {
  public:
    Derived(T &value, demo_initialize initialize = demo_initialize::a) : Base(initialize), mValue(value), mLen(sizeof(T)) {}

    void display() { 
        std::cout << "Derived<T>{" << mValue << "; " << Base::mInitialize << "}";
    }
  protected:
    T &mValue;
    size_t mLen;
};

int main()
{
    std::string string_to_reference = "world";
    Derived<std::string> hello(string_to_reference, demo_initialize::c);
}
