#include <utility>
#include <string>
#include <iostream>

enum EType{
    eInt,
    eBool,
    eFloat,
    eString
};

template<EType type>
decltype(auto) convert(std::string texttoconvert);

template<>
decltype(auto) convert<eInt>(std::string texttoconvert) {
    return std::stoi(texttoconvert);
}
template<>
decltype(auto) convert<eFloat>(std::string texttoconvert) {
    return std::stof(texttoconvert);
}

struct Test
{
    template<EType type>
    decltype(auto) SomeMethod(std::string texttoconvert)
    {
        return convert<type>(texttoconvert);
    }
};

int main() {
    Test t;
    float f = t.SomeMethod<eFloat>("3.14");
    std::cout << f << "\n";
}

