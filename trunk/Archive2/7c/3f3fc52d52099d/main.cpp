#include <boost/scope_exit.hpp>

void Test(int i) {
  auto p = new int;
  BOOST_SCOPE_EXIT_ALL(&) { delete p; };
  
  if (i == 0) return;
  if (i == 1) throw 0;  
}

int main() {
  Test(0);
}