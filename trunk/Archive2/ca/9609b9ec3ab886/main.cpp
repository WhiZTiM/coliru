#include <iostream>
#include <vector>

using namespace std;

class Test {
  public:
    int value;
    Test *next;
};

less<Test> l;

int main(int argc, const char *argv[]) {

  vector<Test> things(5);

  int i = 2;
  for (auto &thing : things) {
    thing.value = i;
    i *= i;
  }

  Test &aCertainThing = things[2];

  cout << l(&aCertainThing, things.data());

  return 0;
}
