#include <iostream>
#include <unordered_map>
#include <functional>
using namespace std;

class KeyBinding {
public:

  void add(int key, function<void()> func) {
    keyToFn.emplace(key, move(func));
  }

  void keyPress(int key) {
    keyToFn[key]();
  }

  unordered_map<int, function<void()>> keyToFn;
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