#include <algorithm>
#include <memory>
#include <vector>

struct data{
  int number;
};

bool comparator(const std::shared_ptr<data> &a, const std::shared_ptr<data> &b) {
    return a->number < b->number;
}

int main() {
  std::vector<std::shared_ptr<data>> v;
  std::sort(v.begin(), v.end(), comparator);
}
