#include <boost/scope_exit.hpp>

void X() {}
void Y() {}

void Test1(int i) {
  auto p = new int;
  BOOST_SCOPE_EXIT_ALL(&) { delete p; };
  
  if (i == 0) return;
  X();
  if (i == 1) throw 0;
  Y();
}

void Test2(int i) {
  auto p = new int;
  if (i == 0) goto exit0;
  X();
  if (i == 1) {
    delete p;
    return;
  }      
  Y();
  exit0:
  delete p;
}

int main() {}