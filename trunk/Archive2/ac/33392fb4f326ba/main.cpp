#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <type_traits>

class C {
  std::string Name;
  int Age;
  
  friend struct C_comp;

public:
  C(const std::string &Name, int Age) : Name(Name), Age(Age) {}
  
  friend std::ostream& operator<<(std::ostream &o, const C &c) {
    o << c.Name << " is " << c.Age << " years old";
    return o;
  }
};

struct C_comp {
  typedef std::true_type is_transparent;
  
  bool operator()(const C &lhs, const C &rhs) const {
    return lhs.Name < rhs.Name;
  }
  
  bool operator()(const C &lhs, const std::string &rhs) const {
    return lhs.Name < rhs;
  }
  
  bool operator()(const std::string &lhs, const C &rhs) const {
    return lhs < rhs.Name;
  }
};

void f() {
  std::set<C, C_comp> s{{"Aaron", 36}, {"Elissa", 31}, {"Bob", 12}};
  
  auto I = s.find("Aaron");
  if (I != s.end())
    std::cout << *I << std::endl;
  else
    std::cout << "Could not find Aaron in the list" << std::endl;
}

int main() {
  f();
}
