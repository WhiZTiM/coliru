#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> get_name_list()
{
    std::string name1 = "foo";
    std::string name2 = "bar";

    std::vector<std::string> names;
    names.push_back(name1);
    names.push_back(name2);
    return names;
}

int main()
{
    std::vector<std::string> list;
    list = get_name_list();
}

