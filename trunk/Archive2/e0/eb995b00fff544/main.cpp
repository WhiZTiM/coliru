#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

// Rotate the range around the first element found by predicate and then
// reverse the elements rotated to the end.
template <typename It, typename F>
void Foo(It first, It last, F f) {
  std::reverse(std::rotate(first, std::find_if(first, last, f), last), last);
}

// Print comma separated lines of range.
template <typename It>
void Print(It first, It last) {
  if (first == last) return;
  std::cout << *first;
  while (++first != last) std::cout << ", " << *first;
  std::cout << "\n";
}

template<typename It>
void Test(It first, It last) {
  Foo(first, last, [](auto x) { return x > 4; });
  Print(first, last);
}


int main() {
  std::vector<int> v{4, 3, 2, 1, 5, 6, 7, 8, 9, 10};
  std::list<int> l{4, 3, 2, 1, 5, 6, 7, 8, 9, 10};
  Test(v.begin(), v.end());
  Test(l.begin(), l.end());
}