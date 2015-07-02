#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;

// the Root hierarchy

class Root {
public:
  virtual ~Root() {}
};

class A : public Root {};

class B : public Root {};


// the Wrapper hierarchy

template<typename T>
class WrapperRoot {
public:
  virtual ~WrapperRoot() {}
  virtual T name() = 0;
};

template<typename T>
class WrapperA : public WrapperRoot<T> {
public:
  virtual T name() { return T("WrapperA\n"); }
};

template<typename T>
class WrapperB : public WrapperRoot<T> {
public:
  virtual T name() { return T("WrapperB\n"); }
};

// util
template<typename T, typename... Args>
auto make_unique(Args... args) -> unique_ptr<T> {
  return unique_ptr<T>(new T(forward<Args>(args)...));
}

// the "wrap" function I want to implement
template<typename T>
auto wrap(Root& root) -> unique_ptr<WrapperRoot<T>>
{
    try {
        auto a = dynamic_cast<A&>(root);
        return make_unique<WrapperA<T>>();
    } 
    catch (std::bad_cast& e) {
        try {
          auto b = dynamic_cast<B&>(root);
          return make_unique<WrapperB<T>>();
        } 
        catch (std::bad_cast& e) {
            throw std::runtime_error("No wrapper for that type");
        }
    }
}



int main() {
  unique_ptr<Root> a = make_unique<A>();
  unique_ptr<Root> b = make_unique<B>();
  cout << wrap<string>(*a)->name()
       << wrap<string>(*b)->name();
}