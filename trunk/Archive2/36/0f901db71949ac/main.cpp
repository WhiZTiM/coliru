#include <iostream>
#include <functional>
#include <vector>
using namespace std;

class SuchString {
    public:
};

template<typename T, class Sel>
class stringSort {
public:    
  void operator() (T& lel) {
      // ...
      std::cout << "normal";
  }
};

template<class Sel>
class stringSort<SuchString, Sel> {
public:
  void operator() (SuchString& lel) {
      // ...
      std::cout << "SuchString";
  }
};

class A1 {
    public:
    void sortStdString(const std::string&) {}
};

class A2 {
    public:
    void sortSuchString(const SuchString&) {}
};

int main()
{
    
    stringSort<std::string, A1> obj;
    std::string sortMe;
    obj(sortMe); // normal
    
    stringSort<SuchString, A2> obj2;
    SuchString sortMeToo;
    obj2(sortMeToo); // such string
    
}