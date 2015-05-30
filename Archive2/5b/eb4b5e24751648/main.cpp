#include <iostream>
#include <string>
#include <vector>
#include <array>

class Thing
{
public:
    struct Bling { int x; };
    void Bling() { };
    
    std::vector<Bling> list_blings;
};

int main()
{
    Thing thing;
    return 0;
}
