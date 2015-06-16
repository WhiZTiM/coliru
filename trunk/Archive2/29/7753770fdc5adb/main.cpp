#include <iostream>
#include <vector>

struct Struct {
    Struct() { std::cout << "empty" << '\n'; }
    Struct(const Struct& s) { std::cout << "copy" << '\n'; }
    Struct(Struct&& s) /*noexcept*/ { std::cout << "move" << '\n'; }
};

std::vector<Struct> vector;

void func() {
    std::cout << "init structs:" << '\n';
    Struct s1, s2;
    std::cout << '\n';
    
    vector.reserve(2);
    
    std::cout << "push_back copy:" << '\n';
    vector.push_back(s1);
    std::cout << '\n';
    
    std::cout << "push_back move:" << '\n';
    vector.push_back(std::move(s2));
    std::cout << '\n';
}

int main()
{
    func();
}