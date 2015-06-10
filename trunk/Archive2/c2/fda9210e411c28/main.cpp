#include <iostream>
#include <string>
#include <map>

#include <map>
#include <string>

struct node{
  std::map<std::string, node> children;
  int a{};
};

int main() {
  node v;
  v.children["foo"].children["bar"].a = 42;
} 