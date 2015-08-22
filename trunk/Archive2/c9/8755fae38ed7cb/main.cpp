#include <iostream>
#include <unordered_map>
#include <utility>
using namespace std;

class KeyBinding {
public:

  void add(int key, void(*func)()) {
    keyToFn.emplace(key, func);
  }

  void keyPress(int key) {
    ((void(*)())keyToFn[key])();
  }

  unordered_map<int, void(*)()> keyToFn;
};

void callMe() {
  cout << "callMe called" << endl;
}

int main() {

  KeyBinding kb;
  kb.add(0xF, &callMe);
  kb.keyPress(0xF);

  return 0;
}