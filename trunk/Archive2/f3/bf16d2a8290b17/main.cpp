#include <iterator>
#include <iostream>
#include <unordered_set>
#include <utility>
#include <set>

template<typename T>
std::unordered_set<T> FailMove(std::set<T> &&set) {
  std::unordered_set<T> response;
  response.insert(std::make_move_iterator(set.begin()),
                  std::make_move_iterator(set.end()));
  return response;
}

int main(int argc, char **argv) {
  std::set<int> set{1, 3, 5, 7};

  auto res = FailMove(std::move(set));
  std::cout << res.size() << '\n';

  return 0;
}