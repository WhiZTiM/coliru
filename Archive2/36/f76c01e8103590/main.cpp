#include <iostream>
#include <array>
#include <string>

class State_code
{ 
  std::array<char,2> code;
 
public:
  constexpr State_code(char const *c) : code{{c[0],c[1]}} {}      
  constexpr State_code(std::string const &s) : code{{s[0],s[1]}} {}
  
  State_code(State_code const &)            = default;
  State_code(State_code &&)                 = default;
  State_code &operator=(State_code const &) = default;
  State_code &operator=(State_code &&)      = default;
  
  auto data() { return code.data(); }
  auto size() { return code.size(); }

  friend bool operator<(State_code l, State_code r) {
    return std::lexicographical_compare(l.code.begin(), l.code.end(),
                                        r.code.begin(), r.code.end());
  }
  
  friend bool operator==(State_code l, State_code r) {
    return l.code == r.code;
  }
  friend bool operator!=(State_code l, State_code r) {
    return l.code != r.code;
  }

  friend std::istream &operator>>(std::istream &is, State_code &s) {
    return is >> s.code[0] >> s.code[1];
  }
  friend std::ostream &operator<<(std::ostream &os, State_code s) {
    return os << s.code[0] << s.code[1];
  }  
};

constexpr State_code no_state{"XX"};

int main() {
  State_code input = no_state;
  if (std::cin >> input && input != no_state)
    std::cout << input << '\n';
  else
    std::cout << "Could not read input state code.\n";
}
