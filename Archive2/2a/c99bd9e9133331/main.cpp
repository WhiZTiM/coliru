#include <iostream>
#include <string>

struct Struct
{
    std::string str;
};

void func(const Struct& s) {
    std::cout << "func(const Struct& s)" << std::endl;
    std::cout << s.str << std::endl;
}

void func(Struct&& s) {
    std::cout << "func(Struct&& s)" << std::endl;
    std::cout << s.str << std::endl;
}

int main()
{
    Struct s = {"named var"};
    func(s);
    
    func(Struct{"unamed temp"});
}