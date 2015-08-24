#include <iostream>
#include <type_traits>
#include <vector>

template<class R,class Test, class T = std::decay_t<decltype(*std::begin(r))>>
auto where(R&& r, Test&& test)
-> std::vector<T>
{
  std::vector<T> ret;
  for(auto&& x:r)
    if(test(x))
      ret.emplace_back(x);
  return ret;
}

int main() {
}