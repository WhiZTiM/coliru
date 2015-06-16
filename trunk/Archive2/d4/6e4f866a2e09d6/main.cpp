#include <string>
#include <iostream>

#include <tuple>

template <typename... Types>
using $ = std::tuple<Types...>;

template <typename... Types>
std::tuple<Types&...> buck_operator(Types&... args) {
  return std::tie(args...);
}

template <typename... Types>
std::tuple<Types...> buck_operator(Types&&... args) {
  return std::tuple<Types...>(args...);
}

#define $(...) buck_operator(__VA_ARGS__)

using namespace std;

// Declare multiple return type with $<>
$<int, string> get_current_user() {
  // Pack the two return values with $()
  return $(0, "root");
}

int main() {
  int id;
  string name;

  // Unpack the two values with $()
  $(id, name) = get_current_user();

  cout << "User ID: " << id << endl;
  cout << "User Name: " << name << endl;

  return 0;
}