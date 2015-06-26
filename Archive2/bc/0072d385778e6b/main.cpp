#include <iostream>
#include <map>
#include <set>
#include <string>
int main()
{
    std::map<int, std::set<std::string>, std::greater<int>> m = {
            {1, {"b", "c", "bar"}},
            {10, {"a", "123"}}};

    for(auto& p: m) {
        std::cout << p.first << " -> ";
        for(auto& s: p.second) {
            std::cout << s << ' ';
        }
        std::cout << '\n';
    }
}
