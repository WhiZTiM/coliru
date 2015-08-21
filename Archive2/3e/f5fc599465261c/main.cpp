#include <map>
#include <iostream>
typedef std::multimap<std::string, int> MapType;

int main()
{

    MapType myMap;

    // insertion
    myMap.insert(MapType::value_type("test", 42));
    myMap.insert(MapType::value_type("test", 45));
    myMap.insert(MapType::value_type("other-test", 0));

    // search
    auto range = myMap.equal_range("test");
    for (auto it = range.first; it != range.second; ++it)
        std::cout << "value for " << it->first << " can be " << it->second << std::endl;
}
