#include <iostream>
#include <map>
#include <string>

struct node {
  std::map<std::string, node> c;
};

int main() {
  node root;
  root.c["alphabet"].c["a"];
  root.c["alphabet"].c["b"];
  root.c["alphabet"].c["c"];
  root.c["alphabet"].c["d"];
  root.c["alphabet"].c["e"];
  root.c["numbers"].c["1"];
  root.c["numbers"].c["2"];
  root.c["numbers"].c["3"];
  root.c["numbers"].c["4"];
  root.c["numbers"].c["5"];
  
  for (auto outer = root.c.begin() ; outer != root.c.end() ; ++outer) {
      std::cout << "- " << outer->first << std::endl;
      for (auto inner = outer->second.c.begin() ; inner != outer->second.c.end() ; ++inner) {
          std::cout << "  - " << inner->first << std::endl;
      }
  }
}
