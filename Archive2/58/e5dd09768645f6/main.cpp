#include <map>
#include <iostream>

int main() {
  std::multimap<int, int> xs;
  xs.insert(std::make_pair(1, 12));
  xs.insert(std::make_pair(1, 11));
  xs.insert(std::make_pair(3, 33));
  xs.insert(std::make_pair(2, 21));
  xs.insert(std::make_pair(2, 22));
  xs.insert(std::make_pair(2, 23));
 
  xs.insert(std::make_pair(3, 32));
  xs.insert(std::make_pair(3, 33));
  xs.insert(std::make_pair(3, 31));

 // List all of the values associated with key betwen 2 and 5.
std::multimap<int, int>::iterator it = xs.begin();//xs.lower_bound(2);
std::multimap<int, int>::iterator end = xs.upper_bound(2);
for (; it != end; ++it) {
  std::cout << it->first << " : " << it->second << std::endl;
  xs.erase(it);
}
 
 
 
}