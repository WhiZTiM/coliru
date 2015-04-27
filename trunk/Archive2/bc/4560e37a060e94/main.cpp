#include <iostream>
#include <string>
#include <functional>

int main()
{
    int start = 100;
    auto fn = [start]() mutable {std::cout << start++ << '\n';};
    
    std::function<void()> f1 = fn;
    std::function<void()> f2 = f1;
    
    std::cout << "f1:\n";
    f1();
    f1();
    f1();
    
    std::cout << "f2:\n";
    f2();
    
    std::cout << "fn:\n";
    fn();
    fn();
    
    std::cout << "copy of fn:\n";
    f1 = fn;
    f1();
    f1();
}
