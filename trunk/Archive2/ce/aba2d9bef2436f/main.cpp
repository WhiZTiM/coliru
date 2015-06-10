#include <iostream>
#include <utility>

template<typename Fun, typename... T>
auto for_each(Fun&& f, T&&... args) 
{
return (std::forward<Fun>(f)(std::forward<T>(args)), ...); // Expanded as f(argument0), f(argument1), ... (comma operator)
}

double doubleVal(double val) {
    std::cout << "Calculating double for value " << val << std::endl;
    return val*2;
}

int main()
{
    double myVal = 56.0, myVal2 = 3.0;
    
    auto ret = for_each(&doubleVal, myVal, myVal2);
    std::cout << ret << std::endl;
}
