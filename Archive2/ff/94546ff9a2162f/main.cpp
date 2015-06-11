#include <iostream>

struct Struct {
   Struct() {};
   Struct(const Struct&) { std::cout << "1" << std::endl; }
   Struct(Struct&&) { std::cout << "2" << std::endl; }
};

struct Struct2 {
    Struct s;
    Struct2(Struct&& s) : s(std::move(s)) {}
};

int main()
{
    //test 1
    Struct s;
    Struct2 s2(std::move(s));
    
    //test 2:
    auto func1 = [](Struct&& s){ std::cout << "a" << std::endl; };
    auto func2 = [func1](Struct&& s){ func1(std::move(s)); };
    func2(Struct());
}