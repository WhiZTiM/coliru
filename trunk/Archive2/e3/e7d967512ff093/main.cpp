#include <map>
#include <utility>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

ostream &operator<<(ostream &os, pair<int, string> const &p) {
    return os << "[" << p.first << ", " << p.second << "]";
}

int main() {
    map<char, pair<int, string>> myMap;
    for (int i = 0; i < 10; i++) {
        char c = 'a' + i;
        pair<int, string> p = make_pair(rand() % 2, "dd");
        myMap.insert(make_pair(c, p));
    }

    std::cout << "before:\n";
    for (auto const &p : myMap)
        std::cout << p.first << ": " << p.second << "\n";

    map<char, pair<int, string> >::iterator it;
    while (myMap.end() != (it = find_if(myMap.begin(), myMap.end(), [](auto p) { return p.second.first == 0; })))
        myMap.erase(it);

    std::cout << "\nafter\n\n";
    for (auto const &p : myMap)
        std::cout << p.first << ": " << p.second << "\n";

}
