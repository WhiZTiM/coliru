#include <iostream>
#include <map>
#include <string>

struct type
{
    int field ;
};

void func(const std::string& name, std::map<std::string, type>& map)
{
    map[name].field = 3 ;
}

int main()
{
    std::map<std::string, type> map ;
    std::string name = "name" ;
    func(name, map);
    std::cout << map["name"].field ;
    return 0;
}