#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>

int main() {
    std::unordered_map<int, int> um {{2, 3}, {6, 7}, {0, 5}};
    std::vector<std::pair<int, int>> sorted_elements(um.begin(), um.end());
    std::sort(sorted_elements.begin(), sorted_elements.end());
    for(auto &&p : sorted_elements) std::cout << "(" << p.first << ", " << p.second << ") ";
    std::cout << std::endl;
}