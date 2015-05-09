#include <iostream>
#include <vector>
#include <string>

class A;

class T {
  private:
  
  friend class A;
  
  T(std::string s) : str(s) {}
  
  std::string str;
};


class A {
  public:
  
  A() {
   
   vec.emplace_back("hello");
      
  }
  
  std::vector<T> vec;
    
};

int main() {

  A obj;

  return 0;
}