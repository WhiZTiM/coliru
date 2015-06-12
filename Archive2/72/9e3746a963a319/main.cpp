#include <iostream>

struct boom {
    int i { 42 };
    
    ~boom() { std::cout << "boom\n"; }
};

int main()
{
    auto&& i = boom {}.i;
    std::cout << i << '\n';
}
