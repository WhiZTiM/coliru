#include <unordered_map>
#include <string>

template<typename SYNC>
struct ProductX;

//-- CRTP base class with some sync/lock mechanism
template<typename T, typename SYNC>
struct Base {};
template<typename SYNC>
struct Base<ProductX<SYNC>, SYNC> {
  static std::unordered_map<int, std::string> s_map;
  static SYNC s_sync;
};

//-- derived class using CRTP
template<typename SYNC>
struct ProductX : public Base<ProductX<SYNC>, SYNC> {};

//-- static initialisation
template<typename SYNC>
std::unordered_map<int, std::string> Base<ProductX<SYNC>, SYNC>::s_map {
  { 1, "value_1" },
  { 2, "value_2" }
};

int main() {}