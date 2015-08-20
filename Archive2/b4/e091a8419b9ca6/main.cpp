#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

int main()
{
    std::map<std::string, std::vector<std::string>> dependencyList;
    
    // initialize
    dependencyList["A"] = {"B", "C", "D"};
    dependencyList["B"] = {"F"};
    dependencyList["C"] = {"B", "F"};
    dependencyList["D"] = {"C"};
    
    
    std::unordered_map<std::string, size_t> dependencyCounts;
    
    // use hash map to count dependencies
    for (auto&& dependee : dependencyList)
    {
        if (dependencyCounts.find(dependee.first) == std::end(dependencyCounts))
            dependencyCounts[dependee.first] = 0;
            
        for (auto&& dependedOn : dependee.second)
        {
            if (dependencyCounts.find(dependedOn) == std::end(dependencyCounts))
                dependencyCounts[dependedOn] = 0;
            ++dependencyCounts[dependedOn];
        }
    }
    
    // pull values out of hash map
    using vectype = std::pair<std::string, size_t>;
    std::vector<vectype> sortedVector (std::begin(dependencyCounts), std::end(dependencyCounts));
    
    std::sort(sortedVector.begin(), sortedVector.end(), [](const vectype& lhs, const vectype& rhs){return lhs.second >= rhs.second;});
    
    for (auto&& dependedOn : sortedVector)
        std::cout << dependedOn.first << " ";
    std::cout << std::endl;
}
