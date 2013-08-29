#include <iostream>
#include <string>
#include <vector>

template<typename T>
const std::string& name_of(T&& t = T())
{
    static std::string result = [](std::string s) {
        auto offset = s.find("= ") + 2;
        return s.substr(offset, s.find(";") - offset);
    }(__PRETTY_FUNCTION__);
    return result;
}

int main()
{
    std::cout << name_of(name_of<int>) << std::endl;
    std::cout << name_of(name_of<name_of<int>>) << std::endl;
}