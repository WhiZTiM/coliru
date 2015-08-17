#include <iostream>
#include <vector>

using namespace std;

class Test {
  public:
    int value;
    Test *next;
};

less<Test*> l;

int main(int argc, const char *argv[]) {

  vector<Test> things(5);
  vector<Test> sub(things.begin(), things.begin() + 3);

  cout << "sub size: " << sub.size() << endl;

  int i = 1, n = 2;
  for (auto &thing : things) {
    thing.value = n;
    n *= n;
    thing.next = &things[i++ % 5];
  }

  for (auto &thing : things) {
    bool isInSub = !l(thing.next, sub.data()) && l(thing.next, sub.data() + sub.size());
    cout << isInSub << endl;
  }

  return 0;
}
