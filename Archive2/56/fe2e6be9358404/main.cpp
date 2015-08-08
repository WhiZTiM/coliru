// http://stackoverflow.com/questions/31897319/implementation-of-non-increasing-list-with-stl-c
#include <set>
#include <iostream>
 
int main()
{
  std::set<std::multiset<int, std::greater<int>>>
  myList {{
      {1,5,4,3},
      {2,7,3,1,5},
      {1,9,1,7,3,7,2},
      {2,7,5,3,1},     // duplicate of {2,7,3,1,5}
      {3,5,4,2,3}
  }};
  
  for(auto it = myList.rbegin(); it != myList.rend(); ++it) {
      std::cout << "(";
      for(auto i : *it) {
          std::cout << " " << i;
      }
      std::cout << ")\n";
  }
}