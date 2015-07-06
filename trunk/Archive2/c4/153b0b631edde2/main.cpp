#include <iostream>
#include <map>
#include <vector>

int main()
{
    std::vector<int> data {1, 1, 1, 3, 3, 3, 3, 8, 8};
    std::map<int, int> frequency;
    for(int i: data)
        ++frequency[i];
    for(const auto& e: frequency)
        std::cout << "Element " << e.first << " encountered " << e.second << " times\n";
}
