#include <algorithm>
#include <iostream>
#include <vector>

// Rotate the range around the first element found by predicate and then
// sort the elements rotated to the end;
template <typename It, typename F>
void Foo(It first, It last, F f) {
  std::sort(std::rotate(first, std::find_if(first, last, f), last), last);
}

// Print comma separated lines of range
template <typename It>
void Print(It first, It last) {
  if (first == last) return;
  std::cout << *first;
  while (++first != last) std::cout << ", " << *first;
  std::cout << "\n";
}

int main() {
  std::vector<int> v{2, 1, 3, 4, 5, 6, 7, 8, 9, 10};
  auto first = v.begin();
  auto last = v.end();
  Foo(first, last, [](auto x) { return x > 4; });
  Print(first, last);
}