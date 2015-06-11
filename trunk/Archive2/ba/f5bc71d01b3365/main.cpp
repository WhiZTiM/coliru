#include <iostream>
#include <string>
using namespace std;

int main() {
  string s[5] = "hello";
  reverse(begin(s), end(s));
  cout << *s << endl;
  return 0;
}