#include <iostream>
#include <utility>
#include <tuple>

template<typename Fun, typename... T>
auto for_each_execute_f_return_tuple(Fun&& f, T&&... args) // Returns a tuple applying f to every args
{
    return std::make_tuple( f(std::forward<T>(args)) ... ); // NOT a fold expression, template parameter pack expansion
}

template<typename Fun, typename... T>
auto for_each_execute_f_return_last_element(Fun&& f, T&&... args) // Executes f on each one of args, drops the result and return the last one
{
    return (f(std::forward<T>(args)), ...); // C++17 Fold Expression - expanded as f(argument0), f(argument1), ... (comma operator)
}

double squareVal(double val) {
    std::cout << "Calculating square for value " << val << std::endl;
    return val*val;
}

int main() {
    double myVal = 34.0, myVal2 = 3.0;
    
    double result1, result2;
    std::tie(result1, result2) = for_each_execute_f_return_tuple(&squareVal, myVal, myVal2);
    std::cout << "[" << result1 << "," << result2 << "]" << std::endl; // tuple [1156, 9]
    
    double result3;
    result3 = for_each_execute_f_return_last_element(&squareVal, myVal, myVal2);
    std::cout << result3 << std::endl; // 9
}
