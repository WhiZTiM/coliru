#include <set>
#include <iostream>
 
int main()
{
  std::set<std::multiset<int, std::greater<int>>> set{{{1,5,4,3},{2,7,3,1,5},{1,9,1,7,3,7,2},{3,5,4,2,3}}};
  for(auto it = set.rbegin(); it != set.rend(); ++it) {
      std::cout << "(";
      for(auto i : *it) {
          std::cout << " " << i;
      }
      std::cout << ")\n";
  }
}