#include <unordered_set>
#include <set>
#include <string>
#include <iterator>
#include <vector>

template <typename T>
class TD;

int main(void) {
  std::unordered_set<std::string> s1 = {"a", "b"};
  auto it = s1.begin();
  TD<decltype(it)> td;
  return 0;
}