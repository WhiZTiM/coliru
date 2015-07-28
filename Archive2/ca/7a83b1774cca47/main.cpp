#include <iostream>
#include <type_traits>

template<typename Float, typename std::enable_if<std::is_floating_point<Float>::value>::type* = nullptr>
void func(Float floatVal)
{
    std::cerr << "float: " << floatVal << "\n";
}

template<typename Integer, typename std::enable_if<!std::is_floating_point<Integer>::value && std::is_integral<Integer>::value>::type* = nullptr>
void func(Integer integer)
{
    std::cerr << "integral: " << integer << "\n";
}

int main()
{
    func(32.4246);
    func(144532);
}

