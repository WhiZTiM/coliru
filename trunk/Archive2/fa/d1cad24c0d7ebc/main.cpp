#include <iostream>

extern constexpr int func (int);

template<class T = int>
struct impl {
  friend constexpr int func (T) { return 1; }
};

template<int(*pf)(int), int = pf(0)>
constexpr bool check (int) {
  return true;
}

template<int(*pf)(int)>
constexpr int check (...) {
  return false;
}

int main () {
#ifdef TOUCH
  &func; // touch the address of `func` once, and it will be stuck as undefined
#endif
  impl<int> {};
  constexpr int b = check<&func> (0);

  std::cout << b << std::endl;
}