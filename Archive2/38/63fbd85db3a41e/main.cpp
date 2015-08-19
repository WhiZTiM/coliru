#include <iostream>
#include <string>
#include <vector>

struct Variant {
  enum class Tag { kString, kVector } tag_;
    
  union {
    std::string s_;
    std::vector<char> v_;
  };
  
  Variant(std::string const &s) : tag_{Tag::kString}, s_{s} {}
  Variant(std::vector<char> const &v) : tag_{Tag::kVector}, v_{v} {}
  Variant(Variant const &other) {
    // fill in the blank
  }
  ~Variant() {
    // fill in the blank
  }
};

int main () {
  Variant v1{std::string{"Hello"}};
  Variant v2{std::vector<char>{'h', 'e', 'l', 'l', 'o'}};
}