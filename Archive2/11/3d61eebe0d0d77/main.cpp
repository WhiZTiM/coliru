#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

template <class Container>
void func(Container& c)
{
  using std::begin; // if c is an array, the function will still compile
  using std::end;
  std::for_each(begin(c), end(c), [](int& a) { std::cout << a; });
}

int main()
{
    int a[] = {1, 2, 3};
    func(a);
}