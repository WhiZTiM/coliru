#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>
#include <list>

int main()
{
    std::list<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    c.erase(std::remove(c.begin(), c.end(), 3));
    
    for (auto &i : c) {
        std::cout << i;
    }
}