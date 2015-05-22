#include <iostream>
#include <string>
#include <vector>
#include <map>

int main()
{
    std::map<int, std::vector<std::string>> map;
    map.emplace(5, std::vector<std::string>{"asdf"});
}
